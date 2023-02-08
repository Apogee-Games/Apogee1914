#include "UnitInformationWidget.h"

void UUnitInformationWidget::AddUnit(UUnit* Unit)
{
	if (Units.IsEmpty())
	{
		FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	}
	Units.Add(Unit);
	UpdateCountText();
}

void UUnitInformationWidget::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);
	UpdateCountText();
}

bool UUnitInformationWidget::IsEmpty() const
{
	return Units.IsEmpty();
}

void UUnitInformationWidget::UpdateCountText()
{
	CountTextBlock->SetText(FText::FromString(FString::FromInt(Units.Num())));
}
