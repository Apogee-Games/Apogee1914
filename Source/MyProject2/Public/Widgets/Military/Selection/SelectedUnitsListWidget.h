#pragma once
#include "SelectedMilitaryBranchUnitsListWidget.h"
#include "SelectedUnitsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
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

	void Init();
	
	void SetSelections(const TArray<FUnitsSelection>& Selections);
private:
	UPROPERTY()
	TArray<USelectedMilitaryBranchUnitsListWidget*> MilitaryBranchUnitsListWidgets;
};