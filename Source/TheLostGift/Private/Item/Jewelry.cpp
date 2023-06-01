// Copyright © 2023 FireTaleStudio.

#include "Item/Jewelry.h"

void UJewelry::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);

	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UJewelry::CreateItem(const FItemGenerationParams& ItemGenerationParams)
{
	UE_LOG(LogTemp, Error, TEXT("Jewelry"));
}
