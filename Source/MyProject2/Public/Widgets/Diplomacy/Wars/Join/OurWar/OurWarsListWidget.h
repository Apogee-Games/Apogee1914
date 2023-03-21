﻿#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Diplomacy/Instances/War.h"
#include "OurWarsListWidget.generated.h"

UCLASS()
class UOurWarsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* WarsListView;

	void SetCountry(UCountry* ProvidedCountry);
	
	void SetSelectedWar(UWar* War);
private:
	UPROPERTY()
	UCountry* Country;
};
