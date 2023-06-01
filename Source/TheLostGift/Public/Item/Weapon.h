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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FString Rarity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FString ItemSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MaxStackAmount;
	
	virtual void SetupData(const TMap<FString, FString>& Data) override;
	
private:
	virtual void CreateItem() override;
};