#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "SelectedUnitsWidget.generated.h"

UCLASS()
class USelectedUnitsWidget: public UUserWidget, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitsNumberTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateUnitsCollectionButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* RemoveAllUnitsButton;
	
	void Init(EMilitaryBranch MilitaryBranch = EMilitaryBranch::Army); // TODO: Remove default and add other branches :)
	
	void SetSelectedUnits(const TSet<UUnit*>& Units) const;

	virtual void UnitIsRemoved(UUnit* Unit) override;
private:
	EMilitaryBranch MilitaryBranch;
	
	UFUNCTION()
	void OnCreateUnitsCollectionButtonClick();

	UFUNCTION()
	void OnRemoveAllUnitsButtonClick();
};
