// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Editor/EditorStructs.h"
#include "TheLostGiftGameInstance.generated.h"

UCLASS(Blueprintable)
class THELOSTGIFT_API UTheLostGiftGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TMap<FString, FMobDrops> DropList;
};