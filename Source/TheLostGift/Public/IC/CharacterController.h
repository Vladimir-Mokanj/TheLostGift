// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "CharacterState.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

UCLASS()
class THELOSTGIFT_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterController();

	virtual void Tick(float) override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;
	
	/** Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* SetDestinationClickAction;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnInputCompleted();

private:
	UCharacterState* CharacterState;
};