// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterParameters.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELOSTGIFT_API UCharacterParameters : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
		float Rotation;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
		float StoppingDistance;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
		float Acceleration;
};