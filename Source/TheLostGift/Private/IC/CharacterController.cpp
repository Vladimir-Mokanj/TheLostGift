// Copyright © 2023 FireTaleStudio.

#include "IC/CharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "IC/CharacterState.h"

ACharacterController::ACharacterController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ACharacterController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (FHitResult Hit; GetHitResultUnderCursor(ECC_Visibility, true, Hit))
		if (FVector::Dist(GetPawn()->GetActorLocation(), Hit.Location) > 75.0f)
			CharacterState->Location = (Hit.Location - GetPawn()->GetActorLocation()).GetSafeNormal();
		else
			CharacterState->Location = FVector::Zero();
}

void ACharacterController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Bind the character state
	CharacterState = GetCharacter()->FindComponentByClass<UCharacterState>();
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ACharacterController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ACharacterController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ACharacterController::OnInputCompleted);
	}
}

void ACharacterController::OnInputStarted()
{
	CharacterState->IsPressed = true;
}

void ACharacterController::OnInputCompleted()
{
	CharacterState->IsPressed = false;
}