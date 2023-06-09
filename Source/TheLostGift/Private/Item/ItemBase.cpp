// Copyright © 2023 FireTaleStudio.

#include "Item/ItemBase.h"

int32 UItemBase::GetHashCode() const
{
	return NameToId(Name);
}

int32 UItemBase::NameToId(const FString& Str)
{
	int32 Hash = 2166136261;
	constexpr int32 Prime = 16777619;
	
	for(int i = 0; i < Str.Len(); i++)
	{
		Hash ^= Str[i];
		Hash *= Prime;
	}

	return Hash;
}