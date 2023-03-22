#pragma once
#include "Blueprint/UserWidget.h"
#include "Administration/Instances/Country.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "WarManagementWidget.generated.h"

UCLASS()
class UWarManagementWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* AskToJoinTheirWarButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* AskThemToJoinWarButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DeclareWarButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	void Init();

	void SetCountry(UCountry* ProvidedCountry);

	void RefreshData();
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;

	UFUNCTION()
	void OnDeclareWarButtonClick();

	UFUNCTION()
	void OnAskToJoinTheirWarButtonClick();

	UFUNCTION()
	void OnAskThemToJoinWarButtonClick();
};
