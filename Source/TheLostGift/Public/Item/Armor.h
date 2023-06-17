// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Armor.generated.h"

UCLASS(Blueprintable)
class THELOSTGIFT_API UArmor : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UTexture2D* RaritySprite;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FString ItemSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 MaxStackAmount;

	virtual void SetupData(const TMap<FString, FString>& Data) override;

private:
	virtual void CreateItem(const FVector& DropLocation) override;
};