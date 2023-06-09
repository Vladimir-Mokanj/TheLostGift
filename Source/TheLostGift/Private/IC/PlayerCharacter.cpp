// Copyright © 2023 FireTaleStudio.

#include "IC/PlayerCharacter.h"
#include "IC/CharacterParameters.h"
#include "IC/CharacterState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterState = CreateDefaultSubobject<UCharacterState>(TEXT("CharacterState"));
	CharacterParameters = CreateDefaultSubobject<UCharacterParameters>(TEXT("CharacterParameters"));
}

void APlayerCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (CharacterState->IsPressed)
		AddMovementInput(CharacterState->Location);
}