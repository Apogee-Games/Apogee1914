#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "CountryDiplomacyWidget.generated.h"

UCLASS()
class UCountryDiplomacyWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CountryFlag;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountryNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateNonAggressionPactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DeclareWarButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateDefencivePactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* NonAggressionPactCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* EnemyCountriesListView;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* DefencivePactCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* AlliedCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	void Init();
	
	void SetCountry(UCountry* ProvidedCountry);

	void RefreshData();
private:
	UPROPERTY()
	TMap<int32, UListView*> Lists;
	
	UPROPERTY()
	UCountry* OwnerCountry;

	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnCreateNonAggressionPactButtonClick();

	UFUNCTION()
	void OnDeclareWarButtonClick();

	UFUNCTION()
	void OnCreateDefencivePactButton();
};