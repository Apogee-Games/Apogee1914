
#include "Widgets/Military/Selection/SelectedUnitsWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsWidget::Init(EMilitaryBranch ProvidedMilitaryBranch)
{
	CreateUnitsCollectionButton->OnClicked.AddDynamic(this, &USelectedUnitsWidget::OnCreateUnitsCollectionButtonClick);
	MilitaryBranch = ProvidedMilitaryBranch;
}

void USelectedUnitsWidget::SetSelectedUnits(const TSet<UUnit*>& Units) const
{
	UnitsListView->ClearListItems();
	for (const auto& Unit: Units)
	{
		UnitsListView->AddItem(Unit);
	}

	UnitsNumberTextBlock->SetText(FText::FromString(FString::FromInt(Units.Num())));
}

void USelectedUnitsWidget::OnCreateUnitsCollectionButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	UUnitsFactory* Factory = GetWorld()->GetSubsystem<UUnitsFactory>();
	UUnitsCollection* UnitsCollection = Factory->CreateUnitCollection(MilitaryBranch, Pawn->GetRuledCountry());
	for (const auto& Unit: UnitsListView->GetListItems())
	{
		UnitsCollection->Add(Cast<UUnit>(Unit));
	}
	Pawn->UnitSelectionComponent->SelectUnits(UnitsCollection);
}
