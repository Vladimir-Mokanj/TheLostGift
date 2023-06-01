// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Editor/EditorStructs.h"
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
		void CreateItemBlueprint(const FItemGenerationParams& ItemGenerationParams);
	
	virtual void SetupData(const TMap<FString, FString>& Data);

private:
	virtual void CreateItem(const FItemGenerationParams& ItemGenerationParams) { }
};
