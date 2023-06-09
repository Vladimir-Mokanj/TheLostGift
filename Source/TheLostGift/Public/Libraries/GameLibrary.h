// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameLibrary.generated.h"

class UTheLostGiftGameInstance;

UCLASS()
class THELOSTGIFT_API UGameLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
		static const UTheLostGiftGameInstance* GetGameInstance();
};