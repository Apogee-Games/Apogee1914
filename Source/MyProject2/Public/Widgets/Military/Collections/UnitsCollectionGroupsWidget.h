#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "UnitsCollectionGroupsWidget.generated.h"

UCLASS()
class UUnitsCollectionGroupsWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionGroupsListView;

	void AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

	void RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);
};
