// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataImporter.generated.h"

class UItem;
class UReadCSVData;

UCLASS(Blueprintable)
class UItemDataImporter : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
		void ReadCSVFile(const int32& DataSheetID);

	UItemDataImporter();
	
private:
	TArray<FString> DataSheetValues;
	const FString URL = "https://docs.google.com/spreadsheets/d/1yc6pffdBGonPIqwydl65_LVC69GeDAhFsV9qB6AjRlI/export?format=csv&gid=";

	UPROPERTY()
		UReadCSVData* ReadCSVData;

	UFUNCTION()
		void OnCSVDownloaded(TArray<FString> CSVLines);

	UBlueprint* FindOrCreatePDTBlueprint(const FString& ItemFolderPath, const FString& ItemName, const FString& ItemType) const;
	void FillBlueprintPDTObjectProperties(UItem* BlueprintItem, const TArray<FString>& CSVColumns);
	UItem* GetItemTypeByBlueprint(const UBlueprint* BlueprintAsset, const FString& ItemType) const;
	TSubclassOf<UItem> GetClassByType(const FString& ItemType) const;
	void CreateBlueprintPDTAsset(const TArray<FString>& CSVColumns);
};