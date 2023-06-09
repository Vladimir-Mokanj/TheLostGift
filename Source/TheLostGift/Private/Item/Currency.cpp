// Copyright © 2023 FireTaleStudio.

#include "Item/Currency.h"
#include "GameItems/GameItemCurrency.h"

void UCurrency::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);

	Rarity = Data["Rarity"];
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

	const AGameItemCurrency* SpawnedActor = World->SpawnActor<AGameItemCurrency>(ItemBlueprintClass, DropLocation, FRotator::ZeroRotator);
	if (ItemMesh == nullptr)
		return;
	
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}