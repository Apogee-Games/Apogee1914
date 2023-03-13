#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"

#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupCreationObserver(this);

	GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnitCollection(EMilitaryBranch::Army);
	GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnitCollection(EMilitaryBranch::Army);
	GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnitCollection(EMilitaryBranch::Navy);
	GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnitCollectionGroup(EMilitaryBranch::Navy);
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

