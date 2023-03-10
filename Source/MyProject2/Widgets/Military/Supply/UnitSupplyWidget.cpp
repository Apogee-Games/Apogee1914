#include "UnitSupplyWidget.h"

void UUnitSupplyWidget::Init(UUnit* Unit)
{
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
	UnitWasSupplied(Unit);
}

void UUnitSupplyWidget::UnitWasSupplied(UUnit* Unit)
{
	FString Result = "";
	for (const auto& [GoodName, GoodCount]: Unit->GetEquipmentNeeds())
	{
		const int MaxGoodCount = Unit->GetUnitTypeEquipmentRequirement(GoodName);
		Result += GoodName.ToString() + ": " + FString::FromInt(MaxGoodCount - GoodCount) + "/" + FString::FromInt(MaxGoodCount);
	}
	UnitNeedsTextBlock->SetText(FText::FromString(Result));
}
