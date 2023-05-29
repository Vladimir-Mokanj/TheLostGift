// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LootTable.generated.h"

struct FDrop;

UCLASS()
class THELOSTGIFT_API ULootTable : public UDataTable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<FDrop> ZombieLootDrops;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<FDrop> SkeletonLootDrops;
	
	ULootTable();
};