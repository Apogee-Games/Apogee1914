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

	
	const TArray<UMilitaryBranchDescription*> MilitaryBranches = GetGameInstance()->GetSubsystem<UUnitsFactory>()->GetMilitaryBranches();

	for (const auto& MilitaryBranch: MilitaryBranches)
	{
		UMilitaryBranchUnitsCollectionsListWidget* Widget = CreateWidget<UMilitaryBranchUnitsCollectionsListWidget>(GetOwningPlayer(), MilitaryBranchUnitsCollectionsListWidgetClass); 
		Widget->Init(MilitaryBranch);
		MilitaryBranchesUnitsCollectionsScrollBox->AddChild(Widget);
		MilitaryBranchUnitsCollectionsListWidget.Add(MilitaryBranch, Widget);
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