// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "IInteract.generated.h"

UINTERFACE()
class UIInteract : public UInterface
{
	GENERATED_BODY()
};

class IIInteract
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void TryInteract();
};