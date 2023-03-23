#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"

#include "Administration/Managers/ProvinceManager.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupCreationObserver(this);
}

void UUnitsCollectionsWidget::UnitsCollectionIsCreated(UUnitsCollection* UnitsCollection)
{
	if (!DefaultCollectionGroups.Contains(UnitsCollection->GetMilitaryBranch()))
	{
		UUnitsCollectionGroup* UnitsCollectionGroup = NewObject<UUnitsCollectionGroup>();
		UnitsCollectionGroup->Init(UnitsCollection->GetMilitaryBranch());
		DefaultCollectionGroups.Add(UnitsCollection->GetMilitaryBranch(), UnitsCollectionGroup);
		CollectionsGroupsListView->AddItem(UnitsCollectionGroup);
	}
	DefaultCollectionGroups[UnitsCollection->GetMilitaryBranch()]->Add(UnitsCollection);
}

void UUnitsCollectionsWidget::UnitsCollectionGroupIsCreated(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	CollectionsGroupsListView->AddItem(UnitsCollectionGroup); 
}

void UUnitsCollectionsWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionGroupCreationObserver(this);
}

