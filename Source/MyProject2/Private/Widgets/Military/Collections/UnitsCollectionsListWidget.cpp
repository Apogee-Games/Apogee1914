#include "Widgets/Military/Collections/UnitsCollectionsListWidget.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupCreationObserver(this);

	MilitaryBranchUnitsCollectionsListWidget.SetNum(MilitaryBranchesNumber);
	for (int i = 0; i < MilitaryBranchesNumber; ++i)
	{
		MilitaryBranchUnitsCollectionsListWidget[i] = CreateWidget<UMilitaryBranchUnitsCollectionsListWidget>(GetOwningPlayer(), MilitaryBranchUnitsCollectionsListWidgetClass);
		MilitaryBranchesUnitsCollectionsScrollBox->AddChild(MilitaryBranchUnitsCollectionsListWidget[i]);
	}
}

void UUnitsCollectionsListWidget::UnitsCollectionIsCreated(UUnitsCollection* UnitsCollection)
{
	MilitaryBranchUnitsCollectionsListWidget[UnitsCollection->GetMilitaryBranch()]->AddUnitsCollection(UnitsCollection);
}

void UUnitsCollectionsListWidget::UnitsCollectionGroupIsCreated(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	MilitaryBranchUnitsCollectionsListWidget[UnitsCollectionGroup->GetMilitaryBranch()]->AddUnitsCollectionGroup(UnitsCollectionGroup);
}

void UUnitsCollectionsListWidget::UnitsCollectionIsRemoved(UUnitsCollection* UnitsCollection)
{
	MilitaryBranchUnitsCollectionsListWidget[UnitsCollection->GetMilitaryBranch()]->RemoveUnistCollection(UnitsCollection);
}

void UUnitsCollectionsListWidget::UnitsCollectionGroupIsRemoved(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	MilitaryBranchUnitsCollectionsListWidget[UnitsCollectionGroup->GetMilitaryBranch()]->RemoveUnitsCollectionGroup(UnitsCollectionGroup);
}

void UUnitsCollectionsListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionGroupCreationObserver(this);
}