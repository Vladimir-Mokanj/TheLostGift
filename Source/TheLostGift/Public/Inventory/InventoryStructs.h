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
		FGuid UniqueId;
	
	UPROPERTY(BlueprintReadWrite)
		UItem* Item;
	
	UPROPERTY(BlueprintReadWrite)
		UTexture2D* BackgroundSprite;

	UPROPERTY(BlueprintReadWrite)
		UTexture2D* ItemSprite;

	UPROPERTY(BlueprintReadWrite)
		FVector2D GridPosition;

	UPROPERTY(BlueprintReadWrite)
		FString ItemSize;
};

USTRUCT(BlueprintType)
struct FItemDisplayData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
		FText Name;

	UPROPERTY(BlueprintReadWrite)
		FText Description;
	
	UPROPERTY(BlueprintReadWrite)
		UTexture2D* RaritySprite;

	UPROPERTY(BlueprintReadWrite)
		UTexture2D* ItemSprite;
};