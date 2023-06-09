// Copyright © 2023 FireTaleStudio.

#include "Libraries/GameLibrary.h"
#include "TheLostGiftGameInstance.h"

const UTheLostGiftGameInstance* UGameLibrary::GetGameInstance()
{
	if (GEngine)
		for (const FWorldContext& Context : GEngine->GetWorldContexts())
			if (const UWorld* World = Context.World())
				if (const UTheLostGiftGameInstance* GameInstance = Cast<UTheLostGiftGameInstance>(World->GetGameInstance()))
					return GameInstance;
	
	return nullptr;
}