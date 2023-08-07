#include "Widgets/Military/Collections/UnitsCollectionsListWidget.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();

	UnitsFactory->OnUnitsCollectionStatusChanged.AddUObject(this, &ThisClass::OnUnitsCollectionStatusChanged);
	UnitsFactory->OnUnitsCollectionGroupStatusChanged.AddUObject(this, &ThisClass::OnUnitsCollectionGroupStatusChanged);
	
	const TArray<UMilitaryBranchDescription*> MilitaryBranches = UnitsFactory->GetMilitaryBranches();

	for (const auto& MilitaryBranch: MilitaryBranches)
	{
		UMilitaryBranchUnitsCollectionsListWidget* Widget = CreateWidget<UMilitaryBranchUnitsCollectionsListWidget>(GetOwningPlayer(), MilitaryBranchUnitsCollectionsListWidgetClass); 
		Widget->Init(MilitaryBranch);
		MilitaryBranchesUnitsCollectionsScrollBox->AddChild(Widget);
		MilitaryBranchUnitsCollectionsListWidget.Add(MilitaryBranch, Widget);
	}
}

void UUnitsCollectionsListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnitsFactory->OnUnitsCollectionStatusChanged.RemoveAll(this);
	UnitsFactory->OnUnitsCollectionGroupStatusChanged.RemoveAll(this);
}

void UUnitsCollectionsListWidget::OnUnitsCollectionStatusChanged(UUnitsCollection* UnitsCollection, EUnitStatus UnitStatus)
{
	if (UnitStatus == EUnitStatus::Formed)
	{
		MilitaryBranchUnitsCollectionsListWidget[UnitsCollection->GetMilitaryBranch()]->AddUnitsCollection(UnitsCollection);
	}
	if (UnitStatus == EUnitStatus::Dissolved)
	{
		MilitaryBranchUnitsCollectionsListWidget[UnitsCollection->GetMilitaryBranch()]->RemoveUnistCollection(UnitsCollection);
	}
}

void UUnitsCollectionsListWidget::OnUnitsCollectionGroupStatusChanged(UUnitsCollectionGroup* UnitsCollectionGroup, EUnitStatus UnitStatus)
{
	if (UnitStatus == EUnitStatus::Formed)
	{
		MilitaryBranchUnitsCollectionsListWidget[UnitsCollectionGroup->GetMilitaryBranch()]->AddUnitsCollectionGroup(UnitsCollectionGroup);
	}
	if (UnitStatus == EUnitStatus::Dissolved)
	{
		MilitaryBranchUnitsCollectionsListWidget[UnitsCollectionGroup->GetMilitaryBranch()]->RemoveUnitsCollectionGroup(UnitsCollectionGroup);
	}
}
