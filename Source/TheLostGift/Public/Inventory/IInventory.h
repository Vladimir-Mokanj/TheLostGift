// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "IInventory.generated.h"

UINTERFACE()
class UIInventory : public UInterface
{
	GENERATED_BODY()
};

class IIInventory
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AddItem();
	virtual void AddItem_Implementation() = 0;
};
