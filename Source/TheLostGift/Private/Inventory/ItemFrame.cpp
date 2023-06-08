// Copyright © 2023 FireTaleStudio.

#include "Inventory/ItemFrame.h"

void UItemFrame::SetItemFrame(UTexture2D* BackgroundSprite, UTexture2D* ItemSprite, FVector2D Position, const TScriptInterface<IIItemFrame> Interface)
{
	Action = Cast<IIItemFrame>(Interface.GetObject());

	if (Action == nullptr)
		UE_LOG(LogTemp, Error, TEXT("SERIOUSLY??"));
}