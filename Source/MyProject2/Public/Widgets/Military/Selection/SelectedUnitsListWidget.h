#pragma once
#include "SelectedUnitsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "SelectedUnitsListWidget.generated.h"

UCLASS()
class USelectedUnitsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	USelectedUnitsWidget* SelectedUnitsWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionsListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionGroupsListView;

	void Init();
	
	void SetSelectedUnits(const TSet<UUnit*>& Units);

	void SetSelectedUnits(const TSet<UUnitsCollection*>& UnitsCollections);
	
	void SetSelectedUnits(const TSet<UUnitsCollectionGroup*>& UnitsCollectionGroups);
};
