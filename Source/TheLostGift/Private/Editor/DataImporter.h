// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "DataImporter.generated.h"

UCLASS(Blueprintable)
class UDataImporter : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
	void ReadCSVFile(const int32& DataSheetID);

private:
	void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	TArray<FString> ParseCSVDataIntoLines(const FString& CSVData);
	TArray<FString> ParseCSVLineIntoColumns(const FString& CSVLine);
	void FillStructFromColumns(const TArray<FString>& CSVColumns);
};
