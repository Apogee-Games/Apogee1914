#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Unit.h"
#include "SelectedUnitsWidget.generated.h"

UCLASS()
class USelectedUnitsWidget: public UUserWidget
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

	void Init(EMilitaryBranch MilitaryBranch);
	
	void SetSelectedUnits(const TSet<UUnit*>& Units) const;
private:
	EMilitaryBranch MilitaryBranch;
	
	UFUNCTION()
	void OnCreateUnitsCollectionButtonClick();

	UFUNCTION()
	void OnRemoveAllUnitsButtonClick();
};
