#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsListWidget::Init()
{
	const TArray<UMilitaryBranchDescription*> MilitaryBranches = GetGameInstance()->GetSubsystem<UUnitsFactory>()->GetMilitaryBranches();
	for (const auto& MilitaryBranch: MilitaryBranches)
	{
		USelectedMilitaryBranchUnitsListWidget* Widget = CreateWidget<USelectedMilitaryBranchUnitsListWidget>(GetOwningPlayer(), SelectedMilitaryBranchUnitsListWidgetCLass);
		Widget->Init(MilitaryBranch);
		UnitsListsScrollBox->AddChild(Widget);
		MilitaryBranchUnitsListWidgets.Add(MilitaryBranch, Widget);
	}
}

void USelectedUnitsListWidget::SetSelections(const TMap<UMilitaryBranchDescription*, FUnitsSelection>& Selections)
{
	for (const auto& [MilitaryBranch, Selection]: Selections)
	{
		MilitaryBranchUnitsListWidgets[MilitaryBranch]->SetSelection(Selection);
	}
}