// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStructs.generated.h"

class UItem;
class IIItemFrame;

USTRUCT(BlueprintType)
struct FItemFrameData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		UItem* Item;
	
	UPROPERTY(BlueprintReadWrite)
		UTexture2D* BackgroundSprite;

	UPROPERTY(BlueprintReadWrite)
		UTexture2D* ItemSprite;

	UPROPERTY(BlueprintReadWrite)
		FVector2D GridPosition;
	
	UPROPERTY(BlueprintReadWrite)
		UObject* InterfaceObject;

	UPROPERTY(BlueprintReadWrite)
		FString ItemSize;
};