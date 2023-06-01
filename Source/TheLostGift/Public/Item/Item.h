// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item.generated.h"

UCLASS(Abstract, NotBlueprintable)
class THELOSTGIFT_API UItem : public UItemBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FString DisplayName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FString Type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 Value;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMesh* ItemMesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UTexture2D* Sprite;

	UFUNCTION(BlueprintCallable)
		void HelloTesT();

	virtual void Hello();
	
	virtual void SetupData(const TMap<FString, FString>& Data);
};
