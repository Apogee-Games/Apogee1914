#pragma once
#include "Blueprint/UserWidget.h"
#include "SelectedUnitsWidget.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Components/ExpandableArea.h"
#include "SelectedMilitaryBranchUnitsListWidget.generated.h"

UCLASS()
class USelectedMilitaryBranchUnitsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	USelectedUnitsWidget* SelectedUnitsWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UExpandableArea* UnitsCollectionsExpandableArea;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionsListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateUnitsCollectionGroupButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionGroupsListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UExpandableArea* UnitsCollectionGroupsExpandableArea;
		
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MilitaryBranchTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UExpandableArea* MilitaryBranchExpandableArea;
	
	void Init(EMilitaryBranch ProvidedMilitaryBranch);
	
	void SetSelection(const FUnitsSelection& Selection);
private:
	EMilitaryBranch MilitaryBranch;
	
	void AddUnits(const FUnitsSelection& Selection);

	void AddUnitsCollection(const FUnitsSelection& Selection);

	void AddUnitsCollectionsGroups(const FUnitsSelection& Selection);

	UFUNCTION()
	void OnCreateUnitsCollectionGroupButtonClick();
};

