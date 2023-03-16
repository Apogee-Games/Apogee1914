#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"

#include "Administration/Managers/ProvinceManager.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupCreationObserver(this);
	
	FUnitDescription UnitDescription = FUnitDescription();
	UnitDescription.UnitName = TEXT("Test:)");
	UnitDescription.MilitaryBranch = TEXT("Army");
	UProvince* Province = GetWorld()->GetSubsystem<UProvinceManager>()->GetProvince(TEXT("CAA001FF"));
	UUnit* Unit1 = GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnit(&UnitDescription, Province, Province->GetOwnerCountry()->GetTag());
	UUnit* Unit2 = GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnit(&UnitDescription, Province, Province->GetOwnerCountry()->GetTag());
	UUnit* Unit3 = GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnit(&UnitDescription, Province, Province->GetOwnerCountry()->GetTag());
	UUnit* Unit4 = GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnit(&UnitDescription, Province, Province->GetOwnerCountry()->GetTag());

	UUnitsCollection* Collection = GetWorld()->GetSubsystem<UUnitsFactory>()->CreateUnitCollection(EMilitaryBranch::Army);
	Collection->Add(Unit1);
	Collection->Add(Unit2);
	Collection->Add(Unit3);
	Collection->Add(Unit4);

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

