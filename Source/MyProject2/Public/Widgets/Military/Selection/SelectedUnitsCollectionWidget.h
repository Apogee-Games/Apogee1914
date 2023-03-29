#pragma once
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "SelectedUnitsCollectionWidget.generated.h"

UCLASS()
class USelectedUnitsCollectionWidget: public UUserWidget, public IUnitRemovalObserver
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
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedUnits(UObject* ProvidedUnitsCollection);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

	virtual void NativeDestruct() override;
	
	virtual void UnitIsRemoved(UUnit* Unit) override;
private:
	UPROPERTY()
	UUnitsCollection* UnitsCollection;

	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnRemoveUnitsCollectionButtonClick();
};
