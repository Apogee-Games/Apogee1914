
#include "Widgets/Military/Supply/UnitSupplyWidget.h"

#include "Widgets/Military/Carriers/GoodNeedCarrier.h"


void UUnitSupplyWidget::SetUnit(UObject* ProvidedUnit)
{
	Unit = Cast<UUnit>(ProvidedUnit);
	for (const auto& [Good, Amount]: Unit->GetSupplyNeeds()->GetRequirements())
	{
		if (AddedGoodNeeds.Contains(Good)) continue;
		UGoodNeedCarrier* Carrier = NewObject<UGoodNeedCarrier>();
		Carrier->Init(Unit->GetSupplyNeeds(), Good);
		SuppliesListView->AddItem(Carrier);
		AddedGoodNeeds.Add(Good);
	}
}

void UUnitSupplyWidget::RefreshData()
{
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
}