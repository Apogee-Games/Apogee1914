
#include "Widgets/Military/Selection/SelectedUnitsCollectionWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void USelectedUnitsCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnButtonClick);
}

void USelectedUnitsCollectionWidget::SetSelectedUnits(UObject* ProvidedUnitsCollection)
{
	UnitsCollection = Cast<UUnitsCollection>(ProvidedUnitsCollection);
}

void USelectedUnitsCollectionWidget::RefreshData()
{
	UnitsListView->ClearListItems();
	for (const auto& Unit: UnitsCollection->GetAll())
	{
		UnitsListView->AddItem(Unit);
	}

	UnitsNumberTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollection->GetSize())));
	const FName MilitaryBranchName = MilitaryBranchNames[static_cast<int>(UnitsCollection->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));
}

void USelectedUnitsCollectionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollection);
}
