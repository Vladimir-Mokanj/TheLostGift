// Copyright © 2023 FireTaleStudio.

#include "Inventory/ItemFrame.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "IC/CharacterInventory.h"

void UItemFrame::SetItemFrame(const FItemFrameData& ItemFrameData, UObject* InterfaceObject)
{
	TArray<FString> Parsed;
	ItemFrameData.ItemSize.ParseIntoArray(Parsed, TEXT("x"));
	
	GetItemOverlayCanvasSlot()->SetSize(FVector2D(FCString::Atoi(*Parsed[1])*44, FCString::Atoi(*Parsed[0])*44));
	GetItemOverlayCanvasSlot()->SetPosition(ItemFrameData.GridPosition);
	GetItemFrameImage()->SetBrushFromTexture(ItemFrameData.BackgroundSprite);
	GetItemImage()->SetBrushFromTexture(ItemFrameData.ItemSprite);
	Action = Cast<IIItemFrame>(InterfaceObject);
	UniqueId = ItemFrameData.UniqueId;
}

void UItemFrame::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Action)
		Action->OnMouseItemFrameEnter(this);

	UE_LOG(LogTemp, Error, TEXT("Mouse is over: %s"), *GetClass()->GetName());
}

void UItemFrame::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (Action)
		Action->OnMouseItemFrameLeave(this);

	UE_LOG(LogTemp, Error, TEXT("Mouse left: %s"), *GetClass()->GetName());
}

FReply UItemFrame::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Error, TEXT("Mouse click is: %s"), *GetClass()->GetName());

	//if (Action)
		//Action->ItemLeftClicked(this);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
