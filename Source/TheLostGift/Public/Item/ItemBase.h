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
	inline static int32 InvalidId = -1; 
	
	UPROPERTY(BlueprintReadWrite)
	int32 Id = GetHashCode();
	
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	int32 GetHashCode() const;

	static int32 NameToId(const FString& Str);
};