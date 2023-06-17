// Copyright © 2023 FireTaleStudio.

#include "Item/Currency.h"
#include "GameItems/GameItemCurrency.h"

void UCurrency::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	if (const FString SpritePath = FString::Printf(TEXT("/Game/_Production/2D/Icons/Inventory/%sItemBgr_Sprite.%sItemBgr_Sprite"), *Data[TEXT("Rarity")], *Data[TEXT("Rarity")]); SpritePath.IsEmpty() == false)
		RaritySprite = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpritePath));

	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UCurrency::CreateItem(const FVector& DropLocation)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString ItemFolderPath = TEXT("/Game/_Production/Blueprints/Items/GameItemCurrency_BP.GameItemCurrency_BP_C");
	UClass* ItemBlueprintClass = LoadClass<AGameItemCurrency>(nullptr, *ItemFolderPath);
	
	if (ItemBlueprintClass == nullptr)
		return;

	AGameItemCurrency* SpawnedActor = World->SpawnActor<AGameItemCurrency>(ItemBlueprintClass, DropLocation, FRotator::ZeroRotator);
	if (ItemMesh == nullptr)
		return;
	
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
	SpawnedActor->SetItemData(this);
}