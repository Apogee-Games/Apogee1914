#pragma once
#include "Widgets/CountrySelection/CountrySelectionWidget.h"

#include "CountrySelectionPawn.generated.h"

UCLASS()
class ACountrySelectionPawn: public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UCountrySelectionWidget> CountrySelectionWidgetClass;

	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UCountrySelectionWidget* CountrySelectionWidget;
};
