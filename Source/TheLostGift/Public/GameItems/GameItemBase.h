// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameItemBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class THELOSTGIFT_API AGameItemBase : public AActor
{
	GENERATED_BODY()

public:
	AGameItemBase();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* ItemStaticMeshComponent;
};