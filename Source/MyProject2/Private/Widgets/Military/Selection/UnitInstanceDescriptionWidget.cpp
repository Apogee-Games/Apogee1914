
#include "Widgets/Military/Selection/UnitInstanceDescriptionWidget.h"

#include "InGameTime.h"
#include "Characters/HumanPlayerPawn.h"
#include "Military/Instances/Units/Unit.h"


void UUnitInstanceDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitInstanceDescriptionWidget::OnClick);
}

void UUnitInstanceDescriptionWidget::Init(UObject* Object) 
{
	Unit = Cast<UUnit>(Object);
	RefreshData();
}

void UUnitInstanceDescriptionWidget::RefreshData() 
{
	FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	ProvinceNameTextBlock->SetText(FText::FromName(Unit->GetPosition()->GetName()));
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
}

void UUnitInstanceDescriptionWidget::OnClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectUnit(Unit);
}
