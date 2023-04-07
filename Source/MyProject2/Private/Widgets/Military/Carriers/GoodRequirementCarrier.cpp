
#include "Widgets/Military/Carriers/GoodRequirementCarrier.h"

void UGoodRequirementCarrier::Init(UUnitDescription* ProvidedUnitDescription, UGoodDescription* ProvidedGood)
{
	UnitDescription = ProvidedUnitDescription;
	Good = ProvidedGood;
}

int32 UGoodRequirementCarrier::GetRequirement() const
{
	return UnitDescription->EquipmentRequirements[Good];
}

const FText& UGoodRequirementCarrier::GetGoodName() const
{
	return Good->NameText;
}
