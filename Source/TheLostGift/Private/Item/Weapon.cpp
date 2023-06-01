// Copyright © 2023 FireTaleStudio.

#include "Item/Weapon.h"

void UWeapon::Hello()
{
	Super::Hello();

	UE_LOG(LogTemp, Error, TEXT("Weapon"));
}

void UWeapon::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}
