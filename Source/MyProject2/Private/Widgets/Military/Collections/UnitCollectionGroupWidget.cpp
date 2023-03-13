
#include "Widgets/Military/Collections/UnitCollectionGroupWidget.h"

void UUnitCollectionGroupWidget::SetUnitsCollectionGroup(UObject* ProvidedUnitsCollectionGroup)
{
	UnitsCollectionGroup = Cast<UUnitsCollectionGroup>(ProvidedUnitsCollectionGroup);
	for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
}

void UUnitCollectionGroupWidget::RefreshData()
{
	const FName MilitaryBranchName = MilitaryBranchNames[static_cast<int>(UnitsCollectionGroup->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));
	CollectionGroupSizeTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollectionGroup->GetSize())));
}
