#include "UnitTypeDescriptionWidget.h"

#include "MyProject2/Characters/HumanPlayerPawn.h"

void UUnitTypeDescriptionWidget::Init(const FUnitDescription* ProvidedUnitDescription)
{
	UnitDescription = ProvidedUnitDescription;
	SetUnitName(ProvidedUnitDescription->UnitName);
	Button->OnClicked.AddDynamic(this, &UUnitTypeDescriptionWidget::OnButtonClick);
}

void UUnitTypeDescriptionWidget::SetUnitName(const FName& UnitName) const
{
	UnitNameTextBlock->SetText(FText::FromName(UnitName));
}

void UUnitTypeDescriptionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectUnitDescription(UnitDescription);
}
