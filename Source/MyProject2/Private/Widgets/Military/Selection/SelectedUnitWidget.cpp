
#include "Widgets/Military/Selection/SelectedUnitWidget.h"

#include "InGameTime.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Managers/UnitsFactory.h"


void USelectedUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitWidget::OnButtonClick);
	RemoveUnitButton->OnClicked.AddDynamic(this, &USelectedUnitWidget::OnRemoveUnitButtonClick);
}

void USelectedUnitWidget::Init(UObject* Object) 
{
	Unit = Cast<UUnit>(Object);
	RefreshData();
}

void USelectedUnitWidget::RefreshData() 
{
	//FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	ProvinceNameTextBlock->SetText(Unit->GetPosition()->GetName());
	UnitNameTextBlock->SetText(FText::FromName(Unit->GetUnitName()));
	ManpowerTextBlock->SetText(FText::FromString(FString::FromInt(Unit->GetManpower())));
}

void USelectedUnitWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnit(Unit);
}

void USelectedUnitWidget::OnRemoveUnitButtonClick()
{
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->RemoveUnit(Unit);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->UnSelectUnit(Unit, true);
}
