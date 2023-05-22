// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemBase.generated.h"

UCLASS(Abstract)
class THELOSTGIFT_API UItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	inline static int InvalidId = -1; 
	
	UPROPERTY(BlueprintReadWrite)
	int Id = GetHashCode();
	
	UPROPERTY(BlueprintReadWrite)
	FString Name = "Item";

	int GetHashCode() const;

	static int NameToId(FString Str);
};
