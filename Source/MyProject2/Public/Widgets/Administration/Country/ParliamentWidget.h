#pragma once
#include "Blueprint/UserWidget.h"
#include "Administration/Instances/Parliament.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "ParliamentWidget.generated.h"

UCLASS()
class UParliamentWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* FractionsListView; 

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ParliamentNameTextBlock;
	
	void SetParliament(UParliament* ProvidedParliament);

	void RefreshData();
private:
	UPROPERTY()
	UParliament* Parliament;
};
