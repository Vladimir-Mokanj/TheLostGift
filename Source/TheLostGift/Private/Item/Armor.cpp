// Copyright © 2023 FireTaleStudio.

#include "Item/Armor.h"
#include "GameItems/GameItemArmor.h"

void UArmor::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UArmor::CreateItem(const FVector& DropLocation)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString ItemFolderPath = TEXT("/Game/_Production/Blueprints/Items/GameItemArmor_BP.GameItemArmor_BP_C");
	UClass* ItemBlueprintClass = LoadClass<AGameItemArmor>(nullptr, *ItemFolderPath);
	
	if (ItemBlueprintClass == nullptr)
		return;
	
	const AGameItemArmor* SpawnedActor = World->SpawnActor<AGameItemArmor>(ItemBlueprintClass, DropLocation, FRotator::ZeroRotator);
	if (ItemMesh == nullptr)
		return;
	
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}