// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "EditorStructs.generated.h"

class UItem;

USTRUCT()
struct FTableData
{
	GENERATED_BODY()

	TWeakObjectPtr<UItem> Item;
	float DropChance;
	int32 MinQuantity;
	int32 MaxQuantity;
};