// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"

#include "DataTableImporter.generated.h"

class UItem;
class UReadCSVData;

UCLASS(Blueprintable)
class UDataTableImporter : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
	void ReadCSVFile(const int32& DataSheetID);

	UDataTableImporter();
	
private:
	TArray<FString> DataSheetValues;
	const FString URL = "https://docs.google.com/spreadsheets/d/1AlrWVhJqLsTT2Tm2zHRlN0KzFllpYh_8VcBHuDgaVuU/export?format=csv&gid=";

	UPROPERTY()
		UReadCSVData* ReadCSVData;

	UFUNCTION()
		void OnCSVDownloaded(TArray<FString> CSVLines);

	//UBlueprint* FindOrCreatePDTBlueprintAsset(const FString& ItemFolderPath, const FString& ItemName, const FString& ItemType) const;
	//void FillBlueprintPDTObjectProperties(UItem* BlueprintDefaultObject, const TArray<FString>& CSVColumns);
	//UItem* GetBlueprintValueByType(const UBlueprint* BlueprintAsset, const FString& ItemType) const;
	//TSubclassOf<UItem> GetClassByType(const FString& ItemType) const;
	//void CreateBlueprintPDTAsset(const TArray<FString>& CSVColumns);
};