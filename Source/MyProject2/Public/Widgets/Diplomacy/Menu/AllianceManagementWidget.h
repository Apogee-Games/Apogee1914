#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "AllianceManagementWidget.generated.h"

UCLASS()
class UAllianceManagementWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceWithAnotherCountryButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* AskThemToJoinAllianceButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* AllianceInteractionsWidgetSwitcher;

	void SetCountry(UCountry* ProvidedCountry);
	
	void Init();
	
	void RefreshData();
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnCreateAllianceWithAnotherButtonClick();

	UFUNCTION()
	void OnCreateAllianceButtonClick();

	UFUNCTION()
	void OnAskToJoinAllianceButtonClick();
};
