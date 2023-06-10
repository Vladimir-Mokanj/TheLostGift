// Copyright © 2023 FireTaleStudio.


#include "IC/CharacterInventory.h"

#include "TheLostGiftGameInstance.h"
#include "Item/Weapon.h"
#include "Libraries/GameLibrary.h"

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

void UCharacterInventory::AddItem_Implementation(const FItemFrameData ItemFrameData)
{
	ItemFrameDataArray.Add(ItemFrameData);
	UE_LOG(LogTemp, Error, TEXT("%i"), ItemFrameDataArray.Num());
	
	InventoryUIDelegate.Broadcast(ItemFrameDataArray);
}

// Called when the game starts
void UCharacterInventory::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayTimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]() {
		// Code to execute after the delay
		if (const UTheLostGiftGameInstance* Instances = UGameLibrary::GetGameInstance())
		{
			const FDrop Drop = Instances->DropList.Find("Skeleton")->Drops[4];
			UWeapon* WeaponInstance = Cast<UWeapon>(NewObject<UItem>(this, Drop.ItemClass));
			
			if (WeaponInstance != nullptr)
			{
				UTexture2D* SpriteBackground = nullptr;
				if (const FString SpritePath = FString::Printf(TEXT("/Game/_Production/2D/Icons/Inventory/%sItemBgr_Sprite.%sItemBgr_Sprite"), *WeaponInstance->Rarity, *WeaponInstance->Rarity); SpritePath.IsEmpty() == false)
					SpriteBackground = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpritePath));

				TArray<FString> Parsed;
				WeaponInstance->ItemSize.ParseIntoArray(Parsed, TEXT("x"));
				const FItemFrameData ItemFrameData = {WeaponInstance, SpriteBackground, WeaponInstance->Sprite, FVector2D(FCString::Atoi(*Parsed[1])*44, FCString::Atoi(*Parsed[0])*44), nullptr};
				AddItem_Implementation(ItemFrameData);
			}
		}
	});

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, TimerDelegate, 1, false);
}