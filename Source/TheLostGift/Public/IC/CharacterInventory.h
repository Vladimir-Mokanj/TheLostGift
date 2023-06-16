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
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FInventoryUIDelegate InventoryUIDelegate;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 InventoryRowSize = 7;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 InventoryColSize = 12;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 FrameSize = 44;
	
	UCharacterInventory();

	virtual void OnStartDrag(UItemFrame* ItemFrame) override;
	virtual void OnEndDrag(UItemFrame* ItemFrame) override;
	virtual void ItemLeftClicked(UItemFrame* ItemFrame) override;
	virtual void AddItem_Implementation(FItemFrameData& ItemFrameData) override;

private:
	TArray<FItemFrameData> ItemFrameDataArray;
	TArray<TArray<bool>> SlotOccupied;
	
	void InitializeSlots();
	FVector2D FindEmptySlot(int ItemWidth, int ItemHeight);
	bool CanPlaceItem(int ItemStartX, int ItemStartY, int ItemWidth, int ItemHeight);
	void ToggleOccupiedSlots(int ItemStartX, int ItemStartY, int ItemWidth, int ItemHeight, const bool IsOccupied);

protected:
	virtual void BeginPlay() override;
};