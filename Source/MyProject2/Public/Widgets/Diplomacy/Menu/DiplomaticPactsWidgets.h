#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "DiplomaticPactsWidgets.generated.h"

UCLASS()
class UDiplomaticPactsWidgets: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateNonAggressionPactButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateDefencivePactButton;

	void Init();
	
	void SetCountry(UCountry* ProvidedCountry);

	void RefreshData();
	
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnCreateNonAggressionPactButtonClick();
	
	UFUNCTION()
	void OnCreateDefencivePactButtonClick();
};
