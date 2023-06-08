// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "IItemFrame.h"
#include "Blueprint/UserWidget.h"
#include "ItemFrame.generated.h"

UCLASS(Blueprintable)
class THELOSTGIFT_API UItemFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetItemFrame(UTexture2D* BackgroundSprite, UTexture2D* ItemSprite, FVector2D Position, TScriptInterface<IIItemFrame> Interface);
	
private:
	IIItemFrame* Action;
};
