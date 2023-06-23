// Copyright © 2023 FireTaleStudio.

#include "IC/CharacterInventory.h"
#include "Inventory/ItemFrame.h"
#include "Item/Item.h"

// Sets default values for this component's properties
UCharacterInventory::UCharacterInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCharacterInventory::BeginPlay()
{
	Super::BeginPlay();

	InitializeSlots();
}

void UCharacterInventory::OnMouseItemFrameEnter(UItemFrame* ItemFrame)
{
	UE_LOG(LogTemp, Error, TEXT("On Mouse Enter"));

	if (!ItemFrameDataMap.Contains(ItemFrame->GetUniqueId()))
		return;

	const FItemFrameData& ItemFrameData = ItemFrameDataMap[ItemFrame->GetUniqueId()];
	FItemDisplayData ItemDisplayData;
	ItemDisplayData.Name = FText::FromString(Cast<UItem>(ItemFrameData.Item)->DisplayName);
	ItemDisplayData.Description = FText::FromString(Cast<UItem>(ItemFrameData.Item)->Description);
	ItemDisplayData.RaritySprite = ItemFrameData.BackgroundSprite;
	ItemDisplayData.ItemSprite = ItemFrameData.ItemSprite;
	
	InventoryDisplayDelegate.Broadcast(ItemDisplayData);
}

void UCharacterInventory::OnMouseItemFrameLeave(UItemFrame* ItemFrame)
{
	if (!ItemFrameDataMap.Contains(ItemFrame->GetUniqueId()))
		return;

	FItemDisplayData EmptyItem;
	InventoryDisplayDelegate.Broadcast(EmptyItem);
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
	
	ItemFrameData.GridPosition = EmptySlot;
	ItemFrameData.UniqueId = FGuid::NewGuid();
	
	ItemFrameDataMap.Add(ItemFrameData.UniqueId, ItemFrameData);
	InventoryUIDelegate.Broadcast(ItemFrameData);
}

void UCharacterInventory::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ItemFramePtr == nullptr)
		return;

	// The parameter for GetMousePosition() is the player controller
	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		UE_LOG(LogTemp, Error, TEXT("Blaa"));
		if (FVector2D MousePosition; PC->GetMousePosition(MousePosition.X, MousePosition.Y))
		{
			UE_LOG(LogTemp, Error, TEXT("Blaa2"));
			ItemFramePtr->SetPositionInViewport(MousePosition, true);
		}
	}
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