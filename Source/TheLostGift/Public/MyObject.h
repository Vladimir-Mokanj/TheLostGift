// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THELOSTGIFT_API UMyObject : public UObject
{
	GENERATED_BODY()

	
public:
	void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	UFUNCTION(BlueprintCallable, Category = "CSV Data")
	void ReadCSVFile();
	
};
