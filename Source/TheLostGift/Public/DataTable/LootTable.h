// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LootTable.generated.h"

struct FTableData;

UCLASS()
class THELOSTGIFT_API ULootTable : public UDataTable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTableData> DataTableRows;
	
	ULootTable();
};