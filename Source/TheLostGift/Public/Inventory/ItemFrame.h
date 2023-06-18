// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "IItemFrame.h"
#include "InventoryStructs.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "ItemFrame.generated.h"

class UImage;

UCLASS(Blueprintable)
class THELOSTGIFT_API UItemFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetItemFrame(const FItemFrameData& ItemFrameData, UObject* InterfaceObject);
	
protected:
	FGuid GetUniqueId() const { return UniqueId; }
	
	UFUNCTION(BlueprintImplementableEvent)
		UCanvasPanelSlot* GetItemOverlayCanvasSlot();

	UFUNCTION(BlueprintImplementableEvent)
		UImage* GetItemFrameImage();

	UFUNCTION(BlueprintImplementableEvent)
		UImage* GetItemImage();

private:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	IIItemFrame* Action;

	FGuid UniqueId;
};