// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "DataTableImporter.generated.h"

struct FTableData;
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

	void CreateBlueprintDTAsset(const TArray<FString>& CSVColumns);
	UBlueprint* FindOrCreateDTBlueprintAsset(const FString& ItemFolderPath/*, const FString& ItemName, const FString& ItemType*/) const;
	void FillBlueprintDTObjectProperties(FTableData* TableData, const TArray<FString>& CSVColumns);
};