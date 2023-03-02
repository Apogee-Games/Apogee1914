#include "UnitSupplyWidget.h"

#include "MyProject2/Military/Instances/GoodNeedCarrier.h"


void UUnitSupplyWidget::SetUnit(UObject* ProvidedUnit)
{
	Unit = Cast<UUnit>(ProvidedUnit);
	for (const auto& [GoodName, Amount]: Unit->GetSupplyNeeds()->GetRequirements())
	{
		if (AddGoodNeeds.Contains(GoodName)) continue;
		UGoodNeedCarrier* Carrier = NewObject<UGoodNeedCarrier>();
		Carrier->Init(Unit->GetSupplyNeeds(), GoodName);
		SuppliesListView->AddItem(Carrier);
		AddGoodNeeds.Add(GoodName);
	}
}

void UUnitSupplyWidget::RefreshData()
{
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
}