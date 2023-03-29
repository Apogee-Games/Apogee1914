
#include "Widgets/Military/Selection/SelectedUnitsWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsWidget::Init(EMilitaryBranch ProvidedMilitaryBranch)
{
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
	
	CreateUnitsCollectionButton->OnClicked.AddDynamic(this, &USelectedUnitsWidget::OnCreateUnitsCollectionButtonClick);
	RemoveAllUnitsButton->OnClicked.AddDynamic(this, &USelectedUnitsWidget::OnRemoveAllUnitsButtonClick);
	
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

void USelectedUnitsWidget::UnitIsRemoved(UUnit* Unit)
{
	UnitsListView->RemoveItem(Unit);
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

	Pawn->UnitSelectionComponent->SelectUnits(UnitsCollection, true);
}

void USelectedUnitsWidget::OnRemoveAllUnitsButtonClick()
{
	UUnitsFactory* Factory = GetWorld()->GetSubsystem<UUnitsFactory>();
	TArray<UObject*> UnitsArrayCopy = UnitsListView->GetListItems();
	for (const auto& Unit: UnitsArrayCopy)
	{
		Factory->RemoveUnit(Cast<UUnit>(Unit));
	}

	// TODO: We can pass array of units to remove and notification will happen only when all of them have benn removed, this way we should get rid of coping :) 
	
	UnitsNumberTextBlock->SetText(FText::FromString(FString::FromInt(0))); 
}
