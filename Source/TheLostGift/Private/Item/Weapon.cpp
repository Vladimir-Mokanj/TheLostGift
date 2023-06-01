// Copyright © 2023 FireTaleStudio.

#include "Item/Weapon.h"

void UWeapon::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UWeapon::CreateItem(const FItemGenerationParams& ItemGenerationParams)
{
	UE_LOG(LogTemp, Error, TEXT("Weapon"));
}