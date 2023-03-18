#pragma once
#include "GameFramework/HUD.h"
#include "Widgets/CountrySelection/CountrySelectionControlsWidget.h"
#include "Widgets/CountrySelection/ScenarioSelectionWidget.h"
#include "Widgets/CountrySelection/SelectedCountryWidget.h"
#include "CountrySelectionHUD.generated.h"

UCLASS()
class ACountrySelectionHUD: public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UScenarioSelectionWidget> ScenarioSelectionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USelectedCountryWidget> SelectedCountryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCountrySelectionControlsWidget> CountrySelectionControlsWidgetClass;

	virtual void BeginPlay() override;
	
	UScenarioSelectionWidget* GetScenarioSelectionWidget() const;

	USelectedCountryWidget* GetSelectedCountryWidget() const;

	UCountrySelectionControlsWidget* GetCountrySelectionControlsWidget() const;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UScenarioSelectionWidget* ScenarioSelectionWidget;

	UPROPERTY()
	USelectedCountryWidget* SelectedCountryWidget;

	UPROPERTY()
	UCountrySelectionControlsWidget* CountrySelectionControlsWidget;
};
