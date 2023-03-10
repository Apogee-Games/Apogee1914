
#include "Widgets/Military/Supply/UnitSupplyWidget.h"

#include "Widgets/Military/Carriers/GoodNeedCarrier.h"


void UUnitSupplyWidget::SetUnit(UObject* ProvidedUnit)
{
	Unit = Cast<UUnit>(ProvidedUnit);
	for (const auto& [GoodName, Amount]: Unit->GetSupplyNeeds()->GetRequirements())
	{
		if (AddedGoodNeeds.Contains(GoodName)) continue;
		UGoodNeedCarrier* Carrier = NewObject<UGoodNeedCarrier>();
		Carrier->Init(Unit->GetSupplyNeeds(), GoodName);
		SuppliesListView->AddItem(Carrier);
		AddedGoodNeeds.Add(GoodName);
	}
}

void UUnitSupplyWidget::RefreshData()
{
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
}