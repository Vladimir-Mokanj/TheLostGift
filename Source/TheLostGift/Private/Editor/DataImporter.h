// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "DataImporter.generated.h"

class UItem;

UCLASS(Blueprintable)
class UDataImporter : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
	void ReadCSVFile(const int32& DataSheetID);

private:
	TArray<FString> DataSheetValues;
	
	void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	TArray<FString> ParseCSVDataIntoLines(const FString& CSVData);
	TArray<FString> ParseCSVLineIntoColumns(const FString& CSVLine);
	UBlueprint* FindOrCreatePDTBlueprintAsset(const FString& ItemFolderPath, const FString& ItemName, const FString& ItemType) const;
	void FillBlueprintPDTObjectProperties(UItem* BlueprintDefaultObject, const TArray<FString>& CSVColumns);
	UItem* GetBlueprintValueByType(const UBlueprint* BlueprintAsset, const FString& ItemType) const;
	TSubclassOf<UItem> GetClassByType(const FString& ItemType) const;
	void CreateBlueprintPDTAsset(const TArray<FString>& CSVColumns);
};
