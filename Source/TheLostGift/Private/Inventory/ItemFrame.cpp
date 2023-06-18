// Copyright © 2023 FireTaleStudio.

#include "Inventory/ItemFrame.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "HUD/GameGUI.h"
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
}

void UItemFrame::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Action)
		Action->OnMouseItemFrameEnter(this);

	UE_LOG(LogTemp, Error, TEXT("Mouse is over: %s"), *GetClass()->GetName());
}

FReply UItemFrame::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Error, TEXT("Mouse click is: %s"), *GetClass()->GetName());

	if (Action)
		Action->ItemLeftClicked(this);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}