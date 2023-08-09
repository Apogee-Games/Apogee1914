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

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UPROPERTY()
	UCountry* Country;
	
	UPROPERTY()
	TMap<ERelationType, UListView*> Lists;

	UFUNCTION()
	void OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation);

	UFUNCTION()
	void OnCountrySelected(UCountry* InCountry);
	
	void RefreshData();
};
