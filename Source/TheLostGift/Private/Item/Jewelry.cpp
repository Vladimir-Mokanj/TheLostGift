// Copyright © 2023 FireTaleStudio.

#include "Item/Jewelry.h"
#include "GameItems/GameItemJewelry.h"

void UJewelry::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);

	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UJewelry::CreateItem()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString BlueprintPath = TEXT("/Game/_Production/Blueprints/Items/GameItemJewelry_BP.GameItemJewelry_BP_C");
	UClass* BlueprintClass = LoadClass<AGameItemJewelry>(nullptr, *BlueprintPath);
	
	if (BlueprintClass == nullptr)
		return;
	
	const FVector Location = FVector(0, 0, 0);
	const AGameItemJewelry* SpawnedActor = World->SpawnActor<AGameItemJewelry>(BlueprintClass, Location, FRotator::ZeroRotator);
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}