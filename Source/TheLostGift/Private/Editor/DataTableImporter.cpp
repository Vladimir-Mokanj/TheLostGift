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

void UDataTableImporter::FillBlueprintDTObjectProperties(FDrop* TableData, const TArray<FString>& CSVColumns) const
{
	if (TableData)
	{
		const FString BlueprintPath = FString::Printf(TEXT("/Game/_Production/Blueprints/Data/%s/%s_PDT.%s_PDT_C"), *CSVColumns[DataSheetValues.Find("Type")], *CSVColumns[DataSheetValues.Find("UItem")], *CSVColumns[DataSheetValues.Find("UItem")]);
		if (BlueprintPath.IsEmpty() == false)
			TableData->ItemClass = StaticLoadClass(UItem::StaticClass(), nullptr, *BlueprintPath);

		TableData->DropChance = FCString::Atof(*CSVColumns[DataSheetValues.Find("DropChance")]);
		TableData->MinQuantity = FCString::Atof(*CSVColumns[DataSheetValues.Find("MinQuantity")]);
		TableData->MaxQuantity = FCString::Atof(*CSVColumns[DataSheetValues.Find("MaxQuantity")]);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("INCORRECT BLUEPRINT DEFAULT OBJECT TYPE"));
}
