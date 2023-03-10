#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Unit.h"
#include "UnitInstancesListDescriptionWidget.generated.h"

UCLASS()
class UUnitInstancesListDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	void SetSelectedUnits(const TArray<UUnit*>& Units) const;
};
