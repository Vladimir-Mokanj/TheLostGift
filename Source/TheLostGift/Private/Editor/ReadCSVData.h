// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "ReadCSVData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCSVDownloaded, TArray<FString>, CSVLines);

UCLASS()
class UReadCSVData : public UObject
{
	GENERATED_BODY()

public:
	FOnCSVDownloaded OnCSVDownloaded;
	
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
		void ReadCSVFile(const FString& DownloadURL, const int32& DataSheetID);

	TArray<FString> ParseCSVLineIntoColumns(const FString& CSVLine);
	
private:
	void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	TArray<FString> ParseCSVDataIntoLines(const FString& CSVData);
};