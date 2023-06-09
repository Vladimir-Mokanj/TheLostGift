// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THELOSTGIFT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCharacterState* CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCharacterParameters* CharacterParameters;
	
	APlayerCharacter();
	
	virtual void Tick(float DeltaSeconds) override;
};