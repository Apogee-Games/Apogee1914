#pragma once
#include "AllianceManagementWidget.h"
#include "DiplomaticPactsWidgets.h"
#include "RelationsListWidget.h"
#include "WarManagementWidget.h"
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
	UDiplomaticPactsWidgets* DiplomaticPactsWidget;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWarManagementWidget* WarManagementWidget;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	URelationsListWidget* RelationsListWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UAllianceManagementWidget* AllianceManagementWidget;

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
};