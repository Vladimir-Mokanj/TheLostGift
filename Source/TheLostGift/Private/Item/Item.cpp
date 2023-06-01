// Copyright © 2023 FireTaleStudio.

#include "Item/Item.h"

void UItem::CreateItemBlueprint(const FItemGenerationParams& ItemGenerationParams)
{
	CreateItem(ItemGenerationParams);
}

void UItem::SetupData(const TMap<FString, FString>& Data)
{
	Id = GetHashCode();
	Name = Data[TEXT("Name")];
	DisplayName = Data[TEXT("DisplayName")];
	Type = Data[TEXT("Type")];
	Value = FCString::Atoi(*Data[TEXT("Value")]);

	if (const FString SpritePath = FString::Printf(TEXT("/Game/_Production/2D/Icons/%s/%s.%s"), *Type, *Data[TEXT("SpriteName")], *Data[TEXT("SpriteName")]); SpritePath.IsEmpty() == false)
		Sprite = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpritePath));
	
	if(const FString ItemMeshPath = FString::Printf(TEXT("/Game/_Production/3D/%s/%s/%s.%s"), *Type, *Name, *Data[TEXT("ItemMesh")], *Data[TEXT("ItemMesh")]); ItemMeshPath.IsEmpty() == false)
		ItemMesh = LoadObject<UStaticMesh>(nullptr, *ItemMeshPath);
}
