// Copyright © 2023 FireTaleStudio.

#include "Item/Item.h"
#include "Item/BaseItemStructure.h"

void UItem::Setup(FBaseItemStructure* DataRow)
{
	Name = DataRow->StaticStruct()->GetName();
	Value = DataRow->Value;
}