// Copyright © 2023 FireTaleStudio.

#include "Item/Weapon.h"

void UWeapon::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);

	Rarity = Data["Rarity"];
}