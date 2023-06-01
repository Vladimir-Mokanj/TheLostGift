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

void UCurrency::CreateItem()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString BlueprintPath = TEXT("/Game/_Production/Blueprints/Items/GameItemCurrency_BP.GameItemCurrency_BP_C");
	UClass* BlueprintClass = LoadClass<AGameItemCurrency>(nullptr, *BlueprintPath);
	
	if (BlueprintClass == nullptr)
		return;
	
	const FVector Location = FVector(0, 0, 0);
	const AGameItemCurrency* SpawnedActor = World->SpawnActor<AGameItemCurrency>(BlueprintClass, Location, FRotator::ZeroRotator);
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}