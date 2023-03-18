
#include "Widgets/CountrySelection/ScenarioSelectionWidget.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CountrySelection/ScenarioDescriptionWidget.h"

void UScenarioSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
	
	TArray<UScenario*> Scenarios = GameInstance->Scenarios;

	for (const auto Scenario: Scenarios)
	{
		ScenariosListView->AddItem(Scenario);
	}

	ActiveScenarioNameTextBlock->SetText(FText::FromName(GameInstance->ActiveScenario->ScenarioName));
}

void UScenarioSelectionWidget::SetScenario(UScenario* Scenario)
{
	ActiveScenarioNameTextBlock->SetText(FText::FromName(Scenario->ScenarioName));
	GetGameInstance<UMyGameInstance>()->SetScenario(Scenario);
}

//	GetGameInstance<UMyGameInstance>()->SetRuledCountry(GetTypeHash(GetOwningPlayer()->GetPlayerState<APlayerState>()->GetUniqueId()), *CountryTagTextBox->GetText().ToString());
