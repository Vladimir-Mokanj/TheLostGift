// Copyright © 2023 FireTaleStudio.

#include "Editor/DataTableImporter.h"

#include "ReadCSVData.h"
#include "AssetRegistry/AssetRegistryModule.h"
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

	
	for (const FString& CSVLine : CSVLines)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *CSVLine);
		//TArray<FString> CSVColumns = ReadCSVData->ParseCSVLineIntoColumns(CSVLine);
		//CreateBlueprintPDTAsset(CSVColumns);
	}
}

//UBlueprint* UDataTableImporter::FindOrCreatePDTBlueprintAsset(const FString& ItemFolderPath, const FString& ItemName, const FString& ItemType) const
//{
//	const UPackage* ExistingPackage = LoadPackage(nullptr, *ItemFolderPath, LOAD_None);
//
//	if (ExistingPackage == nullptr)
//	{
//		// Create new blueprint
//		const FString BlueprintNameString = ItemName + "_PDT";
//		const FName BlueprintName(*BlueprintNameString);
//
//		//UClass* ItemClass = GetClassByType(ItemType);
//		UPackage* Package = CreatePackage(*ItemFolderPath);
//		//return FKismetEditorUtilities::CreateBlueprint(ItemClass, Package, BlueprintName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
//	}
//
//	// Blueprint already exists, fetch it from the existing package
//	for (TObjectIterator<UBlueprint> Itr; Itr; ++Itr)
//		if (Itr->GetOuter() == ExistingPackage)
//			return *Itr;
//	
//	return nullptr;
//}
//
//void UDataTableImporter::FillBlueprintPDTObjectProperties(UItem* BlueprintDefaultObject, const TArray<FString>& CSVColumns)
//{
//	if (BlueprintDefaultObject)
//	{
//		TMap<FString, FString> PropertyMap;
//		const int32 NumColumns = CSVColumns.Num();
//
//		int32 a = DataSheetValues.Num();
//		
//		// Build a map of PropertyName to ColumnValue
//		for (int32 ColumnIndex = 0; ColumnIndex < NumColumns; ++ColumnIndex)
//		{
//			FString PropertyName = DataSheetValues[ColumnIndex];
//			FString ColumnValue = CSVColumns[ColumnIndex];
//			PropertyMap.Add(PropertyName, ColumnValue);
//		}
//
//		//BlueprintDefaultObject->SetupData(PropertyMap);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("INCORRECT BLUEPRINT DEFAULT OBJECT TYPE"));
//	}
//}
//
//void UDataTableImporter::CreateBlueprintPDTAsset(const TArray<FString>& CSVColumns)
//{
//	// Prepare data
//	const FString ItemFolderPath = FString::Printf(TEXT("/Game/_Production/Blueprints/Data/%s/%s_PDT"), *CSVColumns[DataSheetValues.IndexOfByKey("Type")], *CSVColumns[DataSheetValues.IndexOfByKey("Name")]);
//	
//	UBlueprint* BlueprintAsset = FindOrCreatePDTBlueprintAsset(ItemFolderPath, *CSVColumns[DataSheetValues.IndexOfByKey("Name")], *CSVColumns[DataSheetValues.IndexOfByKey("Type")]);
//	
//	// Cast default object to UItem
//	UItem* BlueprintDefaultObject = GetBlueprintValueByType(BlueprintAsset, *CSVColumns[DataSheetValues.IndexOfByKey("Type")]);
//	
//	// Fill up properties for BlueprintDefaultObject
//	FillBlueprintPDTObjectProperties(BlueprintDefaultObject, CSVColumns);
//	
//	// Save the package to disk
//	FAssetRegistryModule::AssetCreated(BlueprintAsset);
//	UPackage::SavePackage(Cast<UPackage>(BlueprintAsset->GetOuter()), BlueprintAsset, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(BlueprintAsset->GetOuter()->GetName(), FPackageName::GetAssetPackageExtension()));
//}