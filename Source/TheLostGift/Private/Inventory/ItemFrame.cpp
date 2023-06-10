// Copyright © 2023 FireTaleStudio.

#include "Inventory/ItemFrame.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "IC/CharacterInventory.h"

void UItemFrame::SetItemFrame(const FItemFrameData& ItemFrameData)
{
	GetItemOverlayCanvasSlot()->SetSize(ItemFrameData.Position);
	GetItemFrameImage()->SetBrushFromTexture(ItemFrameData.BackgroundSprite);
	GetItemImage()->SetBrushFromTexture(ItemFrameData.ItemSprite);
	Action = Cast<IIItemFrame>(ItemFrameData.InterfaceObject);
}

void UItemFrame::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Action)
		Action->OnStartDrag(this);

	UE_LOG(LogTemp, Error, TEXT("Mouse is over: %s"), *GetClass()->GetName());
}

FReply UItemFrame::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Error, TEXT("Mouse click is: %s"), *GetClass()->GetName());

	if (Action)
		Action->ItemLeftClicked(this);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}