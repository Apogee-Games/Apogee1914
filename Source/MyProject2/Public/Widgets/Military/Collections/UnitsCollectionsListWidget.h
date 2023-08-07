#pragma once
#include "MilitaryBranchUnitsCollectionsListWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Military/Managers/UnitsFactory.h"
#include "UnitsCollectionsListWidget.generated.h"

UCLASS()
class UUnitsCollectionsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* MilitaryBranchesUnitsCollectionsScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMilitaryBranchUnitsCollectionsListWidget> MilitaryBranchUnitsCollectionsListWidgetClass;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	TMap<UMilitaryBranchDescription*, UMilitaryBranchUnitsCollectionsListWidget*> MilitaryBranchUnitsCollectionsListWidget;

	UPROPERTY()
	UUnitsFactory* UnitsFactory;

	UFUNCTION()
	void OnUnitsCollectionStatusChanged(UUnitsCollection* UnitsCollection, EUnitStatus UnitStatus);

	UFUNCTION()
	void OnUnitsCollectionGroupStatusChanged(UUnitsCollectionGroup* UnitsCollectionGroup, EUnitStatus UnitStatus);

};
