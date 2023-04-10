#pragma once
#include "UnitsCollectionGroupsWidget.h"
#include "UnitsCollectionsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
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

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UBorder* Border;

	void Init(UMilitaryBranchDescription* MilitaryBranch);
	
	void AddUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnistCollection(UUnitsCollection* UnitsCollection);

	void AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

	void RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);
private:
	bool IsUnitsCollectionsEmpty = true;

	bool IsUnitsCollectionsGroupsEmpty = true;

	void UpdateVisibility();
};