// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemStructure.generated.h"

USTRUCT()
struct FBaseItemStructure
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Value;
};