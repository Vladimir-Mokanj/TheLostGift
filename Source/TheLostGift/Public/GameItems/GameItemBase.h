// Copyright © 2023 FireTaleStudio.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameItemBase.generated.h"

UCLASS()
class THELOSTGIFT_API AGameItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
