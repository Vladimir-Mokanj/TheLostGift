// Copyright © 2023 FireTaleStudio.

#include "Item/DataTableBase.h"
#include "Item/BaseItemStructure.h"

UDataTableBase::UDataTableBase()
{
	RowStruct = FBaseItemStructure::StaticStruct();
}
