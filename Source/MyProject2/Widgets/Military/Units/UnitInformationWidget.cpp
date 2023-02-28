#include "UnitInformationWidget.h"

#include "MyProject2/Characters/HumanPlayerPawn.h"

void UUnitInformationWidget::Init()
{
	Button->OnClicked.AddDynamic(this, &UUnitInformationWidget::OnClicked);
}

void UUnitInformationWidget::AddUnit(FUnit* Unit)
{
	if (Units.IsEmpty())
	{
		FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	}
	Units.Add(Unit);
	UpdateCountText();
}

void UUnitInformationWidget::RemoveUnit(FUnit* Unit)
{
	Units.Remove(Unit);
	UpdateCountText();
}

bool UUnitInformationWidget::IsEmpty() const
{
	return Units.IsEmpty();
}

void UUnitInformationWidget::OnClicked()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectUnits(Units);
}

void UUnitInformationWidget::UpdateCountText()
{
	CountTextBlock->SetText(FText::FromString(FString::FromInt(Units.Num())));
}
