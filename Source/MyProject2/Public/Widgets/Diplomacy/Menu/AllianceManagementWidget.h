﻿#pragma once
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
	UWidgetSwitcher* AllianceInteractionsWidgetSwitcher;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceWithAnotherCountryButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* AskThemToJoinAllianceButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* AskToJoinTheirAllianceButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* LeaveAllianceButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DissolveAllianceButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* AllianceCreationDeletionWidgetSwitcher;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void SetCountry(UCountry* ProvidedCountry);
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnCreateAllianceWithAnotherCountryButtonClick();

	UFUNCTION()
	void OnCreateAllianceButtonClick();

	UFUNCTION()
	void OnAskThemToJoinAllianceButtonClick();

	UFUNCTION()
	void OnAskToJoinTheirAllianceButtonClick();

	UFUNCTION()
	void OnLeaveAllianceButtonClick();

	UFUNCTION()
	void OnDissolveAllianceButtonClick();

	UFUNCTION()
	void OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation);

	UFUNCTION()
	void OnCountrySelected(UCountry* InCountry);
	
	void RefreshData();
};
