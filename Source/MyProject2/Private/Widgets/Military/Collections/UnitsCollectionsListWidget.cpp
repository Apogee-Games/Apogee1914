#include "Widgets/Military/Collections/UnitsCollectionsListWidget.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsCollectionsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = GetGameInstance();

	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionRemovalObserver(this);
	
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitsCollectionGroupRemovalObserver(this);

	MilitaryBranchUnitsCollectionsListWidget.SetNum(MilitaryBranchesNumber);
	for (int i = 0; i < MilitaryBranchesNumber; ++i)
	{
		MilitaryBranchUnitsCollectionsListWidget[i] = CreateWidget<UMilitaryBranchUnitsCollectionsListWidget>(GetOwningPlayer(), MilitaryBranchUnitsCollectionsListWidgetClass);
		MilitaryBranchUnitsCollectionsListWidget[i]->Init(MilitaryBranches[i]);
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

	UGameInstance* GameInstance = GetGameInstance();

	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionRemovalObserver(this);
	
	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionGroupCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitsCollectionGroupRemovalObserver(this);
}