// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/IInventory.h"
#include "Inventory/IItemFrame.h"
#include "CharacterInventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELOSTGIFT_API UCharacterInventory : public UActorComponent, public IIItemFrame, public IIInventory
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUIDelegate, const FItemFrameData&, ItemFrameData);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryDisplayDelegate, const FItemDisplayData&, ItemFrameData);
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FInventoryUIDelegate InventoryUIDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FInventoryDisplayDelegate InventoryDisplayDelegate;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 InventoryRowSize = 7;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 InventoryColSize = 12;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 FrameSize = 44;
	
	UCharacterInventory();

	virtual void OnMouseItemFrameEnter(UItemFrame* ItemFrame) override;
	virtual void OnMouseItemFrameLeave(UItemFrame* ItemFrame) override;
	virtual void AddItem_Implementation(FItemFrameData& ItemFrameData) override;

private:
	TMap<FGuid, FItemFrameData> ItemFrameDataMap;
	TArray<TArray<bool>> SlotOccupied;

	UPROPERTY()
		UItemFrame* ItemFramePtr;
	
	void InitializeSlots();
	FVector2D FindEmptySlot(int ItemWidth, int ItemHeight);
	bool CanPlaceItem(int ItemStartX, int ItemStartY, int ItemWidth, int ItemHeight);
	void ToggleOccupiedSlots(int ItemStartX, int ItemStartY, int ItemWidth, int ItemHeight, const bool IsOccupied);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};