// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item.generated.h"

UCLASS(Abstract, NotBlueprintable)
class THELOSTGIFT_API UItem : public UItemBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	int32 Value;
};
