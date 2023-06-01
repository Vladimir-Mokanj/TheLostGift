// Copyright © 2023 FireTaleStudio.


#include "GameItems/GameItemBase.h"

// Sets default values
AGameItemBase::AGameItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item_SM"));
	ItemStaticMeshComponent->SetSimulatePhysics(true);
}

void AGameItemBase::BeginPlay()
{
	Super::BeginPlay();

	//ItemStaticMeshComponent->AddImpulse(FVector(0, 0, 6000000));
}