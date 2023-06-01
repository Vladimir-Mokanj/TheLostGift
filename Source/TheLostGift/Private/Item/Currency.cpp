// Copyright © 2023 FireTaleStudio.

#include "Item/Currency.h"

void UCurrency::SetupData(const TMap<FString, FString>& Data)
{
	Super::SetupData(Data);

	Rarity = Data["Rarity"];
	ItemSize = Data["ItemSize"];
	MaxStackAmount = FCString::Atoi(*Data["MaxStackAmount"]);
}

void UCurrency::CreateItem(const FItemGenerationParams& ItemGenerationParams)
{
	UE_LOG(LogTemp, Error, TEXT("Currency"));
}