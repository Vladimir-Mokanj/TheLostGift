// Copyright © 2023 FireTaleStudio.

#include "Editor/DataTableImporter.h"

#include "ReadCSVData.h"
#include "TheLostGiftGameInstance.h"
#include "Editor/EditorStructs.h"
#include "Item/Item.h"
#include "Kismet2/BlueprintEditorUtils.h"

void UDataTableImporter::ReadCSVFile(const FString& DataSheetName, const int32& DataSheetID)
{
	MonsterName = DataSheetName;
	ReadCSVData->OnCSVDownloaded.AddDynamic(this, &UDataTableImporter::OnCSVDownloaded);
	ReadCSVData->ReadCSVFile(URL, DataSheetID);
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

	// Get the Game Instance and remove the drop list from the monster being updated
	UTheLostGiftGameInstance* TheLostGiftGameInstance = Cast<UTheLostGiftGameInstance>(GameInstanceBlueprintClass->GetDefaultObject());
	TheLostGiftGameInstance->DropList.Remove(MonsterName);

	// Add the new drop list to the map
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
	FDrop BlueprintDefaultObject;
	FMobDrops& ExistingMobDrops = GameInstance->DropList.FindOrAdd(MonsterName);
	
	FillBlueprintDTObjectProperties(&BlueprintDefaultObject, CSVColumns);

	// Add the drops to the loot map
	ExistingMobDrops.Drops.Add(BlueprintDefaultObject);
	GameInstance->DropList.Add(MonsterName, ExistingMobDrops);
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
			else if (DataSheetValues[ColumnIndex] == "ItemActor")
				if (const FString SpritePath = FString::Printf(TEXT("/Game/_Production/Blueprints/Items/WeaponBase_BP.WeaponBase_BP_C")); SpritePath.IsEmpty() == false)
					TableData->ItemActor = LoadObject<UClass>(nullptr, *SpritePath);

		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("INCORRECT BLUEPRINT DEFAULT OBJECT TYPE"));
}