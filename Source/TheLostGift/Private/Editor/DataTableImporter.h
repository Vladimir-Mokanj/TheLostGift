// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "DataTableImporter.generated.h"

class UTheLostGiftGameInstance;
struct FDrop;
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

	void CreateBlueprintDTAsset(UTheLostGiftGameInstance* GameInstance, const TArray<FString>& CSVColumns);
	void FillBlueprintDTObjectProperties(FDrop* TableData, const TArray<FString>& CSVColumns);
};