// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class THELOSTGIFT_API UWeapon : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Rarity;
	
	virtual void SetupData(const TMap<FString, FString>& Data) override;
};
