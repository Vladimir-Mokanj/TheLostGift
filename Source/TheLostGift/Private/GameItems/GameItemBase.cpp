// Copyright © 2023 FireTaleStudio.


#include "GameItems/GameItemBase.h"

// Sets default values
AGameItemBase::AGameItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

