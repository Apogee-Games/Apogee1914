#include "Events/EventInstancesController.h"

#include "MyGameInstance.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UEventInstancesController::CreateEvent(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, UCountryDescription* CountryDescription)
{
	if (WidgetsInstances.Contains({Event, CountryDescription})) return;
	if (Event->TriggerOnce && FiredEvents.Contains({Event, CountryDescription})) return;

	if (static_cast<UMyGameInstance*>(GetWorld()->GetGameInstance())->IsCountryRuledByPlayer(CountryDescription))
	{
		CreateEventForPlayer(Event, ChoicesConditionsEvaluated, CountryDescription);
	}
	else
	{
		CreateEventForAI(Event, ChoicesConditionsEvaluated, CountryDescription);
	}
}

void UEventInstancesController::DeleteEventWidget(UEventDescription* Event, UCountryDescription* CountryDescription)
{
	if (!WidgetsInstances.Contains({Event, CountryDescription})) return;

	WidgetsInstances[{Event, CountryDescription}]->RemoveFromParent();

	WidgetsInstances.Remove({Event, CountryDescription});
}

void UEventInstancesController::Clear()
{
	FiredEvents.Empty();
	Events.Empty();
	ActiveEvents.Empty();
	WidgetsInstances.Empty();
}

void UEventInstancesController::Init(UScenario* Scenario)
{
	Events = Scenario->Events;
	GetGameInstance()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UEventInstancesController::CheckEvents, MinDeltaBetweenEventChecks);
}

void UEventInstancesController::CreateEventForAI(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, UCountryDescription* CountryDescription)
{
	FiredEvents.Add({Event, CountryDescription});

	const FName AISelectedChoice = FindAISelectedChoice(Event->Choices, ChoicesConditionsEvaluated);

	RegisterChoice(Event, AISelectedChoice, CountryDescription);
}

void UEventInstancesController::CreateEventForPlayer(UEventDescription* Event,
                                                     const TMap<FName, bool>& ChoicesConditionsEvaluated,
                                                     UCountryDescription* CountryDescription)
{
	FiredEvents.Add({Event, CountryDescription});

	// TODO: Add multiplayer logic ;)

	UEventWidget* EventWidget = CreateWidget<UEventWidget>(GetWorld(), EventWidgetClass);
	EventWidget->Init(Event, CountryDescription, ChoicesConditionsEvaluated);

	WidgetsInstances.Add({Event, CountryDescription}, EventWidget);
	EventWidget->AddToPlayerScreen();
}

inline float UEventInstancesController::CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices,
                                                                          const TMap<FName, bool>& ChoicesConditionsEvaluated)
{
	float SummedChance = 0;
	for (const auto& Choice : Choices)
	{
		if (!ChoicesConditionsEvaluated[Choice.Name]) continue;
		SummedChance += Choice.AIChance;
	}
	return SummedChance;
}

FName UEventInstancesController::FindAISelectedChoice(const TArray<FEventChoice>& Choices,
                                                      const TMap<FName, bool>& ChoicesConditionsEvaluated) const
{
	const float SummedChance = CalculateSumOfAIChancesForChoices(Choices, ChoicesConditionsEvaluated);

	FName SelectedChoice;

	float Point = FMath::FRandRange(0.0, SummedChance);
	for (const auto& Choice : Choices)
	{
		if (!ChoicesConditionsEvaluated[Choice.Name]) continue;

		if (Point <= Choice.AIChance)
		{
			SelectedChoice = Choice.Name;
			break;
		}

		Point -= Choice.AIChance;
	}

	return SelectedChoice;
}

void UEventInstancesController::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UEventInstancesController::RegisterChoice(UEventDescription* Event, const FName& ChoiceName,
                                               UCountryDescription* CountryDescription)
{
	DeleteEventWidget(Event, CountryDescription);

	for (auto& Choice : Event->Choices)
	{
		if (Choice.Name != ChoiceName) continue;
		GetGameInstance()->GetSubsystem<UOutcomesApplierSubsystem>()->ApplyOutcomes(Choice.Outcomes, CountryDescription);
	}
}

void UEventInstancesController::SetEventWidgetClass(const TSubclassOf<UEventWidget>& NewEventWidgetClass)
{
	EventWidgetClass = NewEventWidgetClass;
}

void UEventInstancesController::Tick(float DeltaTime)
{
	for (const auto& Pair : WidgetsInstances)
	{
		Pair.Value->Tick();
	}
}

void UEventInstancesController::CheckEvents()
{
	UConditionsCheckingSubsystem* ConditionsChecker = GetGameInstance()->GetSubsystem<UConditionsCheckingSubsystem>();
	for (const auto& Event : Events)
	{
		const TArray<UCountryDescription*>& CountryDescriptions = GetCountriesForWhichEventCanBeFired(Event);

		for (auto& CountryDescription : CountryDescriptions)
		{
			if (!ConditionsChecker->CheckConditions(Event->Conditions, CountryDescription)) continue;

			TMap<FName, bool> ChoicesConditionsEvaluated;

			for (auto& Choice : Event->Choices)
			{
				bool Result = ConditionsChecker->CheckConditions(Choice.Conditions, CountryDescription);
				ChoicesConditionsEvaluated.Add(Choice.Name,Result);
			}

			CreateEvent(Event, ChoicesConditionsEvaluated, CountryDescription);
		}
	}
}

const TArray<UCountryDescription*>& UEventInstancesController::GetCountriesForWhichEventCanBeFired(UEventDescription* Event) const
{
	return Event->CountriesConditions.ForAll
		       ? GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountriesDescriptions()
		       : Event->CountriesConditions.CountriesTags;
}
