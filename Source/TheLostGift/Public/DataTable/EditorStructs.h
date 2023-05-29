// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "EditorStructs.generated.h"

class UItem;

USTRUCT(BlueprintType)
struct FTableData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UItem* Item;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float DropChance;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MinQuantity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MaxQuantity;
};