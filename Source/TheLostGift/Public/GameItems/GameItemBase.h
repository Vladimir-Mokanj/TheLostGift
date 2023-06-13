// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameItemBase.generated.h"

class UItem;

UCLASS(Abstract, NotBlueprintable)
class THELOSTGIFT_API AGameItemBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* ItemStaticMeshComponent;

	UPROPERTY()
		UItem* Item;
	
	void SetItemData(UItem* ItemType);
	
	AGameItemBase();

private:
	FTimerHandle StaticItemTimer;
	float CurrentPhysicsTime;
	float MaxPhysicsTime = 3.0f;
	float StaticTimerInRate = 0.3f;

	virtual void BeginPlay() override;
	void ApplyImpulse() const;
	void TryMakeItemStatic(float InRate);
};