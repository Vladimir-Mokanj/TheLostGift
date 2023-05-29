// Copyright © 2023 FireTaleStudio.

#include "Editor/DataTableImporter.h"

#include "ReadCSVData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "DataTable/EditorStructs.h"
#include "DataTable/LootTable.h"
#include "Item/Item.h"
#include "Item/Weapon.h"
#include "Kismet2/KismetEditorUtilities.h"

void UDataTableImporter::ReadCSVFile(const int32& DataSheetID)
{
	ReadCSVData->OnCSVDownloaded.AddDynamic(this, &UDataTableImporter::OnCSVDownloaded);
	ReadCSVData->ReadCSVFile(URL, 0);
}

UDataTableImporter::UDataTableImporter()
{
	ReadCSVData = NewObject<UReadCSVData>();
}

void UDataTableImporter::OnCSVDownloaded(TArray<FString> CSVLines)
{
	// Remove header line
	if (CSVLines.Num() > 0)
	{
		CSVLines[0].ParseIntoArray(DataSheetValues, TEXT(","), true);
		CSVLines.RemoveAt(0);
	}

	const FString ItemFolderPath = FString::Printf(TEXT("/Game/_Production/Blueprints/DataTables/Loot/TestingTable_DT"));
	UBlueprint* BlueprintAsset = FindOrCreateDTBlueprintAsset(ItemFolderPath);
	ULootTable* LootTable = Cast<ULootTable>(BlueprintAsset->GeneratedClass->GetDefaultObject());
	
	for (const FString& CSVLine : CSVLines)
	{
		TArray<FString> CSVColumns = ReadCSVData->ParseCSVLineIntoColumns(CSVLine);
		CreateBlueprintDTAsset(LootTable, CSVColumns);
	}

	// Save the package to disk
	FAssetRegistryModule::AssetCreated(BlueprintAsset);
	UPackage::SavePackage(Cast<UPackage>(BlueprintAsset->GetOuter()), BlueprintAsset, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(BlueprintAsset->GetOuter()->GetName(), FPackageName::GetAssetPackageExtension()));
}

void UDataTableImporter::CreateBlueprintDTAsset(ULootTable* LootTable, const TArray<FString>& CSVColumns)
{
	// Cast default object to UItem
	FTableData* BlueprintDefaultObject = new FTableData();
	
	// Fill up properties for BlueprintDefaultObject
	FillBlueprintDTObjectProperties(BlueprintDefaultObject, CSVColumns);

	LootTable->ZombieLootDrops.Add(*BlueprintDefaultObject);
	LootTable->SkeletonLootDrops.Add(*BlueprintDefaultObject);

	delete BlueprintDefaultObject;
}

UBlueprint* UDataTableImporter::FindOrCreateDTBlueprintAsset(const FString& ItemFolderPath/*, const FString& ItemName, const FString& ItemType*/) const
{
	const UPackage* ExistingPackage = LoadPackage(nullptr, *ItemFolderPath, LOAD_None);

	if (ExistingPackage == nullptr)
	{
		// Create new blueprint
		const FString BlueprintNameString = "TestingTable_DT";
		const FName BlueprintName(*BlueprintNameString);

		UClass* DataTableClass = ULootTable::StaticClass();
		UPackage* Package = CreatePackage(*ItemFolderPath);
		return FKismetEditorUtilities::CreateBlueprint(DataTableClass, Package, BlueprintName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
	}

	// Blueprint already exists, fetch it from the existing package
	for (TObjectIterator<UBlueprint> Itr; Itr; ++Itr)
		if (Itr->GetOuter() == ExistingPackage)
			return *Itr;
	
	return nullptr;
}

void UDataTableImporter::FillBlueprintDTObjectProperties(FTableData* TableData, const TArray<FString>& CSVColumns)
{
	if (TableData)
	{
		const int32 NumColumns = CSVColumns.Num();
		
		// Build a map of PropertyName to ColumnValue
		for (int32 ColumnIndex = 0; ColumnIndex < NumColumns; ++ColumnIndex)
		{
			if (DataSheetValues[ColumnIndex] == "UItem")
			{
				FString BlueprintPath = FString::Printf(TEXT("/Game/_Production/Blueprints/Data/%s/%s.%s_C"), *CSVColumns[DataSheetValues.Find("Type")], *CSVColumns[ColumnIndex], *CSVColumns[ColumnIndex]);

				UClass* ItemClass = StaticLoadClass(UItem::StaticClass(), nullptr, *BlueprintPath);
				TableData->ItemClass = ItemClass;
			}
			else if (DataSheetValues[ColumnIndex] == "DropChance")
				TableData->DropChance = FCString::Atof(*CSVColumns[ColumnIndex]);
			else if (DataSheetValues[ColumnIndex] == "MinQuantity")
				TableData->MinQuantity = FCString::Atoi(*CSVColumns[ColumnIndex]);
			else if (DataSheetValues[ColumnIndex] == "MaxQuantity")
				TableData->MaxQuantity = FCString::Atoi(*CSVColumns[ColumnIndex]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("INCORRECT BLUEPRINT DEFAULT OBJECT TYPE"));
	}
}