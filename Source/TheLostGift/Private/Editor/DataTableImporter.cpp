// Copyright © 2023 FireTaleStudio.

#include "Editor/DataTableImporter.h"

#include "ReadCSVData.h"
#include "TheLostGiftGameInstance.h"
#include "DataTable/EditorStructs.h"
#include "Item/Item.h"
#include "Kismet2/BlueprintEditorUtils.h"

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

	const UClass* GameInstanceBlueprintClass = LoadClass<UObject>(nullptr, TEXT("/Game/_Production/Blueprints/TheLostGift_GI.TheLostGift_GI_C"), nullptr, LOAD_None, nullptr);
	UBlueprint* GameInstanceBlueprint = Cast<UBlueprint>(GameInstanceBlueprintClass->ClassGeneratedBy);

	// You can only change the class default object of a blueprint
	UTheLostGiftGameInstance* TheLostGiftGameInstance = Cast<UTheLostGiftGameInstance>(GameInstanceBlueprintClass->GetDefaultObject());

	for (const FString& CSVLine : CSVLines)
	{
		TArray<FString> CSVColumns = ReadCSVData->ParseCSVLineIntoColumns(CSVLine);
		CreateBlueprintDTAsset(TheLostGiftGameInstance, CSVColumns);
	}

	// This is to apply the changes to the blueprint asset.
	FBlueprintEditorUtils::MarkBlueprintAsModified(GameInstanceBlueprint);
}

void UDataTableImporter::CreateBlueprintDTAsset(UTheLostGiftGameInstance* GameInstance, const TArray<FString>& CSVColumns)
{
	// Cast default object to UItem
	FMobDrops& ExistingMobDrops = GameInstance->DropList.FindOrAdd(TEXT("a"));
	FDrop BlueprintDefaultObject;
	
	// Fill up properties for BlueprintDefaultObject
	FillBlueprintDTObjectProperties(&BlueprintDefaultObject, CSVColumns);

	ExistingMobDrops.Drops.Add(BlueprintDefaultObject);
	GameInstance->DropList.Add("a", ExistingMobDrops);
}

void UDataTableImporter::FillBlueprintDTObjectProperties(FDrop* TableData, const TArray<FString>& CSVColumns)
{
	if (TableData)
	{
		const int32 NumColumns = CSVColumns.Num();
		
		// Build a map of PropertyName to ColumnValue
		for (int32 ColumnIndex = 0; ColumnIndex < NumColumns; ++ColumnIndex)
		{
			if (DataSheetValues[ColumnIndex] == "UItem")
			{
				FString BlueprintPath = FString::Printf(TEXT("/Game/_Production/Blueprints/Data/%s/%s_PDT.%s_PDT_C"), *CSVColumns[DataSheetValues.Find("Type")], *CSVColumns[ColumnIndex], *CSVColumns[ColumnIndex]);

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