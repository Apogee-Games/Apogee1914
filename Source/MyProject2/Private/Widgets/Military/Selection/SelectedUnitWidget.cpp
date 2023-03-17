
#include "Widgets/Military/Selection/SelectedUnitWidget.h"

#include "InGameTime.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Instances/Units/Unit.h"


void USelectedUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitWidget::OnClick);
}

void USelectedUnitWidget::Init(UObject* Object) 
{
	Unit = Cast<UUnit>(Object);
	RefreshData();
}

void USelectedUnitWidget::RefreshData() 
{
	FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	ProvinceNameTextBlock->SetText(FText::FromName(Unit->GetPosition()->GetName()));
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
}

void USelectedUnitWidget::OnClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnit(Unit);
}
