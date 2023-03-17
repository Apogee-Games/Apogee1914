#include "Widgets/CountrySelection/ScenarioDescriptionWidget.h"

#include "Characters/HUDs/CountrySelectionHUD.h"
#include "Characters/Pawns/CountrySelectionPawn.h"

void UScenarioDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UScenarioDescriptionWidget::OnButtonClick);
}

void UScenarioDescriptionWidget::SetScenario(UObject* ProvidedScenario)
{
	Scenario = Cast<UScenario>(ProvidedScenario);
}

void UScenarioDescriptionWidget::RefreshData()
{
	ScenarioNameTextBlock->SetText(FText::FromName(Scenario->ScenarioName));
}

void UScenarioDescriptionWidget::OnButtonClick()
{
	GetOwningPlayer()->GetHUD<ACountrySelectionHUD>()->GetScenarioSelectionWidget()->SetScenario(Scenario);
}
