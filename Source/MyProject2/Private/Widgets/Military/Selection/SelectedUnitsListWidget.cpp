#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"

#include "Military/Instances/Units/Unit.h"

void USelectedUnitsListWidget::Init()
{
	MilitaryBranchUnitsListWidgets.SetNum(MilitaryBranchesNumber);
	for (int i = 0; i < MilitaryBranchesNumber; ++i)
	{
		MilitaryBranchUnitsListWidgets[i] = CreateWidget<USelectedMilitaryBranchUnitsListWidget>(GetOwningPlayer(), SelectedMilitaryBranchUnitsListWidgetCLass);
		MilitaryBranchUnitsListWidgets[i]->Init(MilitaryBranches[i]);
		UnitsListsScrollBox->AddChild(MilitaryBranchUnitsListWidgets[i]);
	}
}

void USelectedUnitsListWidget::SetSelections(const TArray<FUnitsSelection>& Selections)
{
	for (int i = 0; i < Selections.Num(); ++i)
	{
		MilitaryBranchUnitsListWidgets[i]->SetSelection(Selections[i]);
	}
}