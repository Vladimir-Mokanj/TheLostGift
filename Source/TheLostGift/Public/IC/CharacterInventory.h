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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUIDelegate, const TArray<FItemFrameData>&, ItemFrameDataArray);
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FInventoryUIDelegate InventoryUIDelegate;
	
	UCharacterInventory();

	virtual void OnStartDrag(UItemFrame* ItemFrame) override;
	virtual void OnEndDrag(UItemFrame* ItemFrame) override;
	virtual void ItemLeftClicked(UItemFrame* ItemFrame) override;
	virtual void AddItem_Implementation(FItemFrameData ItemFrameData) override;
	
protected:
	virtual void BeginPlay() override;
};