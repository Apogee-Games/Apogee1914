#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "RelationsListWidget.generated.h"

UCLASS()
class URelationsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* NonAggressionPactCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* EnemyCountriesListView;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* DefencivePactCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* AlliedCountriesListView;

	void Init();

	void SetCountry(UCountry* ProvidedCountry);
	
	void RefreshData();
private:
	UPROPERTY()
	UCountry* Country;
	
	UPROPERTY()
	TMap<int32, UListView*> Lists;
};
