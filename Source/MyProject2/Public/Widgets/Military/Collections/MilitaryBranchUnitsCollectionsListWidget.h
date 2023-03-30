#pragma once
#include "UnitsCollectionGroupsWidget.h"
#include "UnitsCollectionsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "MilitaryBranchUnitsCollectionsListWidget.generated.h"

UCLASS()
class UMilitaryBranchUnitsCollectionsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUnitsCollectionsWidget* UnitsCollectionsWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUnitsCollectionGroupsWidget* UnitsCollectionGroupsWidget;

	void AddUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnistCollection(UUnitsCollection* UnitsCollection);

	void AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

	void RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);
};
