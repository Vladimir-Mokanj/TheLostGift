// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class IIInventory;

UCLASS()
class THELOSTGIFT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCharacterState* CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCharacterParameters* CharacterParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCharacterInventory* CharacterInventory;
	
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
		TScriptInterface<IIInventory> IInventory;
	
	virtual void Tick(float DeltaSeconds) override;
};