// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "IItemFrame.generated.h"

class UItemFrame;

UINTERFACE(Blueprintable)
class UIItemFrame : public UInterface
{
	GENERATED_BODY()
};

class IIItemFrame
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void OnMouseItemFrameEnter(UItemFrame* ItemFrame) = 0;

	UFUNCTION()
		virtual void OnMouseItemFrameLeave(UItemFrame* ItemFrame) = 0;
};