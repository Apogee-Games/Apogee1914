
#include "Widgets/Military/Selection/SelectedUnitsWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsWidget::Init(UMilitaryBranchDescription* ProvidedMilitaryBranch)
{
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

void USelectedUnitsWidget::OnCreateUnitsCollectionButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	
	const TArray<UUnit*>& Units = reinterpret_cast<const TArray<UUnit*>&>(UnitsListView->GetListItems());
	UUnitsCollection* UnitsCollection = GetGameInstance()->GetSubsystem<UUnitsFactory>()->CreateUnitCollection(MilitaryBranch, Pawn->GetRuledCountry(), Units);

	Pawn->UnitSelectionComponent->SelectUnits(UnitsCollection, true, true);
}

void USelectedUnitsWidget::OnRemoveAllUnitsButtonClick()
{
	const TArray<UUnit*>& Units = reinterpret_cast<const TArray<UUnit*>&>(UnitsListView->GetListItems());
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->RemoveUnits(Units);
	
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->UnSelectUnits(Units, true);
}
