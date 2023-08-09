#pragma once
#include "SelectedMilitaryBranchUnitsListWidget.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Components/ScrollBox.h"
#include "SelectedUnitsListWidget.generated.h"

UCLASS()
class USelectedUnitsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* UnitsListsScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USelectedMilitaryBranchUnitsListWidget> SelectedMilitaryBranchUnitsListWidgetCLass;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	TMap<UMilitaryBranchDescription*, USelectedMilitaryBranchUnitsListWidget*> MilitaryBranchUnitsListWidgets;

	UFUNCTION()
	void OnSelectionUpdated(FUnitsSelection UnitsSelection);
};