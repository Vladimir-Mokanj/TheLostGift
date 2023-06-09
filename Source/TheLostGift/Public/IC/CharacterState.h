// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterState.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELOSTGIFT_API UCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite, Category = "Character State")
		bool IsPressed;

	UPROPERTY(BlueprintReadWrite, Category = "Character State")
		FVector Location;
};