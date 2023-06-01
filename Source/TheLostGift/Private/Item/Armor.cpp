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

void UArmor::CreateItem()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString BlueprintPath = TEXT("/Game/_Production/Blueprints/Items/GameItemArmor_BP.GameItemArmor_BP_C");
	UClass* BlueprintClass = LoadClass<AGameItemArmor>(nullptr, *BlueprintPath);
	
	if (BlueprintClass == nullptr)
		return;
	
	const FVector Location = FVector(0, 0, 0);
	const AGameItemArmor* SpawnedActor = World->SpawnActor<AGameItemArmor>(BlueprintClass, Location, FRotator::ZeroRotator);
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}