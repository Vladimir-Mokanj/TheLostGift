// Copyright © 2023 FireTaleStudio.

#include "Editor/ItemDataImporter.h"

#include "ReadCSVData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Item/Armor.h"
#include "Item/Currency.h"
#include "Item/Jewelry.h"
#include "Item/Weapon.h"
#include "Kismet2/KismetEditorUtilities.h"

const TMap<FString, UClass*> ItemClassMap = {
	{ "Weapon", UWeapon::StaticClass() },
	{ "Armor", UArmor::StaticClass() },
	{ "Jewelry", UJewelry::StaticClass() },
	{ "Currency", UCurrency::StaticClass() },
};

void UItemDataImporter::ReadCSVFile(const int32& DataSheetID)
{
	ReadCSVData->OnCSVDownloaded.AddDynamic(this, &UItemDataImporter::OnCSVDownloaded);
	ReadCSVData->ReadCSVFile(URL, DataSheetID);
}

UItemDataImporter::UItemDataImporter()
{
	ReadCSVData = NewObject<UReadCSVData>();
}

void UItemDataImporter::OnCSVDownloaded(TArray<FString> CSVLines)
{
	// Remove header line
	if (CSVLines.Num() > 0)
	{
		CSVLines[0].ParseIntoArray(DataSheetValues, TEXT(","), true);
		CSVLines.RemoveAt(0);
	}

	// Create Blueprint Item
	for (const FString& CSVLine : CSVLines)
	{
		TArray<FString> CSVColumns = ReadCSVData->ParseCSVLineIntoColumns(CSVLine);
		CreateBlueprintPDTAsset(CSVColumns);
	}
}

void UItemDataImporter::CreateBlueprintPDTAsset(const TArray<FString>& CSVColumns)
{
	// Prepare data
	const FString ItemFolderPath = FString::Printf(TEXT("/Game/_Production/Blueprints/Data/%s/%s_PDT"), *CSVColumns[DataSheetValues.IndexOfByKey("Type")], *CSVColumns[DataSheetValues.IndexOfByKey("Name")]);
	UBlueprint* Blueprint = FindOrCreatePDTBlueprint(ItemFolderPath, *CSVColumns[DataSheetValues.IndexOfByKey("Name")], *CSVColumns[DataSheetValues.IndexOfByKey("Type")]);
	
	// Cast default object to UItem
	UItem* Item = GetItemTypeByBlueprint(Blueprint, *CSVColumns[DataSheetValues.IndexOfByKey("Type")]);
	
	// Fill up properties for BlueprintDefaultObject
	FillBlueprintPDTObjectProperties(Item, CSVColumns);
	
	// Save the package to disk
	FAssetRegistryModule::AssetCreated(Blueprint);
	UPackage::SavePackage(Cast<UPackage>(Blueprint->GetOuter()), Blueprint, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(Blueprint->GetOuter()->GetName(), FPackageName::GetAssetPackageExtension()));
}

UBlueprint* UItemDataImporter::FindOrCreatePDTBlueprint(const FString& ItemFolderPath, const FString& ItemName, const FString& ItemType) const
{
	const UPackage* ExistingPackage = LoadPackage(nullptr, *ItemFolderPath, LOAD_None);

	// Create new blueprint
	if (ExistingPackage == nullptr)
	{
		const FString BlueprintNameString = ItemName + "_PDT";
		const FName BlueprintName(*BlueprintNameString);

		UClass* ItemClass = GetClassByType(ItemType);
		UPackage* Package = CreatePackage(*ItemFolderPath);
		return FKismetEditorUtilities::CreateBlueprint(ItemClass, Package, BlueprintName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
	}

	// Blueprint already exists, fetch it from the existing package
	for (TObjectIterator<UBlueprint> Itr; Itr; ++Itr)
		if (Itr->GetOuter() == ExistingPackage)
			return *Itr;
	
	return nullptr;
}

void UItemDataImporter::FillBlueprintPDTObjectProperties(UItem* BlueprintItem, const TArray<FString>& CSVColumns)
{
	if (BlueprintItem)
	{
		TMap<FString, FString> PropertyMap;
		const int32 NumColumns = CSVColumns.Num();
		
		// Build a map of PropertyName to ColumnValue
		for (int32 ColumnIndex = 0; ColumnIndex < NumColumns; ++ColumnIndex)
		{
			FString PropertyName = DataSheetValues[ColumnIndex];
			FString ColumnValue = CSVColumns[ColumnIndex];
			PropertyMap.Add(PropertyName, ColumnValue);
		}

		// Assign the Property values to blueprint item
		BlueprintItem->SetupData(PropertyMap);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("INCORRECT BLUEPRINT DEFAULT OBJECT TYPE"));
}

TSubclassOf<UItem> UItemDataImporter::GetClassByType(const FString& ItemType) const
{
	return ItemClassMap.FindRef(ItemType);
}

UItem* UItemDataImporter::GetItemTypeByBlueprint(const UBlueprint* BlueprintAsset, const FString& ItemType) const
{
	const TSubclassOf<UItem> ItemClass = ItemClassMap.FindRef(ItemType);
	return ItemClass ? Cast<UItem>(BlueprintAsset->GeneratedClass->GetDefaultObject()) : nullptr;
}