#include "Widgets/Military/Selection/SelectedUnitsCollectionGroupWidget.h"

#include "Characters/HumanPlayerPawn.h"


void USelectedUnitsCollectionGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnButtonClick);
}

void USelectedUnitsCollectionGroupWidget::SetSelectedUnits(UObject* ProvidedUnitsCollectionGroup)
{
	UnitsCollectionGroup = Cast<UUnitsCollectionGroup>(ProvidedUnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::RefreshData()
{
	UnitsCollectionListView->ClearListItems();
	for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		UnitsCollectionListView->AddItem(UnitsCollection);
	}

	UnitsCollectionNumberTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollectionGroup->GetSize())));
	
	const FName MilitaryBranchName = MilitaryBranchNames[static_cast<int>(UnitsCollectionGroup->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));
}

void USelectedUnitsCollectionGroupWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollectionGroup);
}
