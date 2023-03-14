#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "SelectedUnitsCollectionGroupWidget.generated.h"

UCLASS()
class USelectedUnitsCollectionGroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MilitaryBranchTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitsCollectionNumberTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedUnits(UObject* UnitsCollectionGroup);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

private:
	UPROPERTY()
	UUnitsCollectionGroup* UnitsCollectionGroup;

	UFUNCTION()
	void OnButtonClick();
};
