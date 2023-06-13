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
	TMap<FGuid, FItemFrameData> ItemFrameDataArray;
	TArray<TArray<bool>> SlotOccupied;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AddItem(UPARAM(ref) FItemFrameData& ItemFrameData);
	virtual void AddItem_Implementation(FItemFrameData& ItemFrameData) = 0;
};
