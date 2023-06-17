// Copyright © 2023 FireTaleStudio.

#include "Item/Weapon.h"
#include "GameItems/GameItemWeapon.h"

void UWeapon::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	if (const FString SpritePath = FString::Printf(TEXT("/Game/_Production/2D/Icons/Inventory/%sItemBgr_Sprite.%sItemBgr_Sprite"), *Data[TEXT("Rarity")], *Data[TEXT("Rarity")]); SpritePath.IsEmpty() == false)
		RaritySprite = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpritePath));
	
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UWeapon::CreateItem(const FVector& DropLocation)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString ItemFolderPath = TEXT("/Game/_Production/Blueprints/Items/GameItemWeapon_BP.GameItemWeapon_BP_C");
	UClass* ItemBlueprintClass = LoadClass<AGameItemWeapon>(nullptr, *ItemFolderPath);
	
	if (ItemBlueprintClass == nullptr)
		return;
	
	AGameItemWeapon* SpawnedActor = World->SpawnActor<AGameItemWeapon>(ItemBlueprintClass, DropLocation, FRotator::ZeroRotator);
	if (ItemMesh == nullptr)
		return;
	
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
	SpawnedActor->SetItemData(this);
}