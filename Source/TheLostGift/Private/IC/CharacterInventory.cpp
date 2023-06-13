// Copyright © 2023 FireTaleStudio.

#include "IC/CharacterInventory.h"
#include "Item/Item.h"

// Sets default values for this component's properties
UCharacterInventory::UCharacterInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UCharacterInventory::BeginPlay()
{
	Super::BeginPlay();

	InitializeSlots();
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

void UCharacterInventory::AddItem_Implementation(FItemFrameData& ItemFrameData)
{
	TArray<FString> Parsed;
	ItemFrameData.ItemSize.ParseIntoArray(Parsed, TEXT("x"));
	const int32 ItemWidth = FCString::Atoi(*Parsed[0]);
	const int32 ItemHeight = FCString::Atoi(*Parsed[1]);

	const FVector2D EmptySlot = FindEmptySlot(ItemWidth, ItemHeight);
	if (EmptySlot.X < 0 && EmptySlot.Y < 0)
		return;
	
	ItemFrameData.Position = EmptySlot;
	ItemFrameDataArray.Add(ItemFrameData.Item->UniqueId, ItemFrameData);
	InventoryUIDelegate.Broadcast(ItemFrameData.Item->UniqueId, ItemFrameData);
}

void UCharacterInventory::InitializeSlots()
{
	SlotOccupied.SetNum(InventoryRowSize);

	for(int32 i = 0; i < SlotOccupied.Num(); i++)
		SlotOccupied[i].Init(false, InventoryColSize);
}

FVector2D UCharacterInventory::FindEmptySlot(const int ItemWidth, const int ItemHeight) {
	for (int i = 0; i <= SlotOccupied.Num() - ItemWidth; i++) 
		for (int j = 0; j <= SlotOccupied[i].Num() - ItemHeight; j++) 
			if (CanPlaceItem(i, j, ItemWidth, ItemHeight)) {
				ToggleOccupiedSlots(i, j, ItemWidth, ItemHeight, true);
				return FVector2D(j * FrameSize, i * FrameSize);
			}
	
	return FVector2D(-1, -1);
}

bool UCharacterInventory::CanPlaceItem(const int ItemStartX, const int ItemStartY, const int ItemWidth, const int ItemHeight)
{
	if (ItemStartX + ItemWidth > InventoryRowSize || ItemStartY + ItemHeight > InventoryColSize) 
		return false;

	for (int32 i = ItemStartX; i < ItemStartX + ItemWidth; i++) 
		for (int32 j = ItemStartY; j < ItemStartY + ItemHeight; j++) 
			if (SlotOccupied[i][j] == true) 
				return false;

	return true;
}

void UCharacterInventory::ToggleOccupiedSlots(const int ItemStartX, const int ItemStartY, const int ItemWidth, const int ItemHeight, const bool IsOccupied)
{
	for (int32 i = ItemStartX; i < ItemStartX + ItemWidth; i++) 
		for (int32 j = ItemStartY; j < ItemStartY + ItemHeight; j++) 
			SlotOccupied[i][j] = IsOccupied;
}