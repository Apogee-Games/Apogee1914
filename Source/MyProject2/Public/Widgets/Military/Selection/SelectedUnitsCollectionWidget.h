#pragma once
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Managers/UnitsFactory.h"
#include "SelectedUnitsCollectionWidget.generated.h"

UCLASS()
class USelectedUnitsCollectionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MilitaryBranchTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitsNumberTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* RemoveUnitsCollectionButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CommanderImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CommanderNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CommanderButton;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedUnits(UObject* ProvidedUnitsCollection);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UUnitsCollection* UnitsCollection;

	UPROPERTY()
	UUnitsFactory* UnitsFactory;
	
	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnRemoveUnitsCollectionButtonClick();

	UFUNCTION()
	void OnCommanderButtonClick();

	UFUNCTION()
	void OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus);
};
