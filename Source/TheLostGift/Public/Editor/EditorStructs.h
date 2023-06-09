// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "EditorStructs.generated.h"

class UItem;

USTRUCT(BlueprintType)
struct FDrop
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TSubclassOf<UItem> ItemClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float DropChance;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MinQuantity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MaxQuantity;
};

USTRUCT(BlueprintType)
struct FMobDrops
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<FDrop> Drops;
};

USTRUCT(BlueprintType)
struct FItemGenerationParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float DropChance;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int MinQuantity;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int MaxQuantity;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FVector DropLocation;
};