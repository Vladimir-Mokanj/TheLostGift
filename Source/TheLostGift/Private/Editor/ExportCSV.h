// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExportCSV.generated.h"

UCLASS(Blueprintable)
class THELOSTGIFT_API UExportCSV : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
public:
	void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
	void ReadCSVFile();
	
};
