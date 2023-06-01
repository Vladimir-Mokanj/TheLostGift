// Copyright © 2023 FireTaleStudio.

#include "Item/Armor.h"

void UArmor::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);
	
	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UArmor::CreateItem(const FItemGenerationParams& ItemGenerationParams)
{
	UE_LOG(LogTemp, Error, TEXT("Armor"));
}
