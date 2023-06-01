// Copyright © 2023 FireTaleStudio.

#include "Item/Weapon.h"
#include "GameItems/GameItemWeapon.h"

void UWeapon::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UWeapon::CreateItem()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FString BlueprintPath = TEXT("/Game/_Production/Blueprints/Items/GameItemWeapon_BP.GameItemWeapon_BP_C");
	UClass* BlueprintClass = LoadClass<AGameItemWeapon>(nullptr, *BlueprintPath);
	
	if (BlueprintClass == nullptr)
		return;
	
	const FVector Location = FVector(0, 0, 0);
	const AGameItemWeapon* SpawnedActor = World->SpawnActor<AGameItemWeapon>(BlueprintClass, Location, FRotator::ZeroRotator);
	SpawnedActor->ItemStaticMeshComponent->SetStaticMesh(ItemMesh);
}