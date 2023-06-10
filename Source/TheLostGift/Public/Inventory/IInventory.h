// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStructs.h"
#include "IInventory.generated.h"

struct FItemFrameData;
UINTERFACE()
class UIInventory : public UInterface
{
	GENERATED_BODY()
};

class IIInventory
{
	GENERATED_BODY()

public:
	TArray<FItemFrameData> ItemFrameDataArray;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AddItem(const FItemFrameData ItemFrameData);
	virtual void AddItem_Implementation(const FItemFrameData ItemFrameData) = 0;
};
