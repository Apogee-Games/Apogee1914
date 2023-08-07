#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!UnitsListsScrollBox->GetChildrenCount()) {
		UUnitsFactory* UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();

		const TArray<UMilitaryBranchDescription*> MilitaryBranches = UnitsFactory->GetMilitaryBranches();
		for (const auto& MilitaryBranch: MilitaryBranches)
		{
			USelectedMilitaryBranchUnitsListWidget* Widget = CreateWidget<USelectedMilitaryBranchUnitsListWidget>(GetOwningPlayer(), SelectedMilitaryBranchUnitsListWidgetCLass);
			Widget->Init(MilitaryBranch);
			UnitsListsScrollBox->AddChild(Widget);
			MilitaryBranchUnitsListWidgets.Add(MilitaryBranch, Widget);
		}
	}

	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->OnSelectionUpdated.AddUObject(this, &ThisClass::OnSelectionUpdated);
}

void USelectedUnitsListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->OnSelectionUpdated.RemoveAll(this);
}

void USelectedUnitsListWidget::OnSelectionUpdated(FUnitsSelection UnitsSelection)
{
	MilitaryBranchUnitsListWidgets[UnitsSelection.MilitaryBranch]->SetSelection(UnitsSelection);
}