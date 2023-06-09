// Copyright © 2023 FireTaleStudio.

#include "GameItems/GameItemBase.h"

// Sets default values
AGameItemBase::AGameItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item_SM"));
	SetRootComponent(ItemStaticMeshComponent);
	
	ItemStaticMeshComponent->SetSimulatePhysics(true);
}

void AGameItemBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AGameItemBase::ApplyImpulse, 0.05f, false);
	GetWorldTimerManager().SetTimer(StaticItemTimer, [this] {TryMakeItemStatic(StaticTimerInRate);}, StaticTimerInRate, true);
}

void AGameItemBase::ApplyImpulse() const
{
	ItemStaticMeshComponent->AddImpulse(FVector(FMath::RandRange(-150.0f, 150.0f), FMath::RandRange(-150.0f, 150.0f), 0));
}

void AGameItemBase::TryMakeItemStatic(const float InRate)
{
	CurrentPhysicsTime += InRate;
	if (GetVelocity().Size() > 0.05f && CurrentPhysicsTime <= MaxPhysicsTime)
		return;

	ItemStaticMeshComponent->SetSimulatePhysics(false);
	GetWorldTimerManager().ClearTimer(StaticItemTimer);
}