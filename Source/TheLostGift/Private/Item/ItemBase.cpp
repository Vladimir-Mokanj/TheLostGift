// Copyright © 2023 FireTaleStudio.

#include "Item/ItemBase.h"

int UItemBase::GetHashCode() const
{
	return NameToId(Name);
}

int UItemBase::NameToId(FString Str)
{
	int Hash1 = 5381;
	int Hash2 = Hash1;

	for (int i = 0; i < Str.Len() && Str[i] != '\0'; i += 2)
	{
		Hash1 = ((Hash1 << 5) + Hash1) ^ Str[i];
		if (i == Str.Len() - 1 || Str[i + 1] == '\0')
			break;

		Hash2 = ((Hash2 << 5) + Hash2) ^ Str[i + 1];
	}

	return Hash1 + (Hash2 * 1566083941);
}