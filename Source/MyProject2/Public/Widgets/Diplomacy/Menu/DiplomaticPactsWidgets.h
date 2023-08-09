#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "DiplomaticPactsWidgets.generated.h"

class UCountry;

UCLASS()
class UDiplomaticPactsWidgets: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateNonAggressionPactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BreakNonAggressionPactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* NonAggressionPactCreationRemovalWidgetSwitcher;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateDefencivePactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BreakDefencivePactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* DefencivePactCreationRemovalWidgetSwitcher;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnCreateNonAggressionPactButtonClick();

	UFUNCTION()
	void OnBreakNonAggressionPactButtonClick();

	UFUNCTION()
	void OnCreateDefencivePactButtonClick();

	UFUNCTION()
	void OnBreakDefencivePactButtonClick();

	UFUNCTION()
	void OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation);

	UFUNCTION()
	void OnCountrySelected(UCountry* InCountry);
	
	void RefreshData();
};
