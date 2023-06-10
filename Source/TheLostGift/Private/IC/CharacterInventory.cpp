// Copyright © 2023 FireTaleStudio.


#include "IC/CharacterInventory.h"

// Sets default values for this component's properties
UCharacterInventory::UCharacterInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterInventory::OnStartDrag(UItemFrame* ItemFrame)
{
	UE_LOG(LogTemp, Error, TEXT("On Start Drag"));
}

void UCharacterInventory::OnEndDrag(UItemFrame* ItemFrame)
{
	UE_LOG(LogTemp, Error, TEXT("On End Drag"));
}

void UCharacterInventory::ItemLeftClicked(UItemFrame* ItemFrame)
{
	UE_LOG(LogTemp, Error, TEXT("On Left Click"));
}

void UCharacterInventory::AddItem_Implementation()
{
	InventoryUIDelegate.Broadcast(ItemFrameDataArray);
	
	UE_LOG(LogTemp, Error, TEXT("Add item"));
}

// Called when the game starts
void UCharacterInventory::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayTimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]() {
		// Code to execute after the delay
		AddItem_Implementation();
		UE_LOG(LogTemp, Error, TEXT("Hello"));
	});
	//AddItem_Implementation();
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, TimerDelegate, 5, false);

}