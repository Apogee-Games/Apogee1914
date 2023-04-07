#include "Events/EventInstancesController.h"

#include "MyGameInstance.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UEventInstancesController::CreateEvent(UEventDescription* Event,
                                            const TMap<FName, bool>& ChoicesConditionsEvaluated,
                                            const FName& CountryTag)
{
	if (WidgetsInstances.Contains({Event, CountryTag})) return;
	if (Event->TriggerOnce && FiredEvents.Contains({Event, CountryTag})) return;

	if (static_cast<UMyGameInstance*>(GetWorld()->GetGameInstance())->IsCountryRuledByPlayer(CountryTag))
	{
		CreateEventForPlayer(Event, ChoicesConditionsEvaluated, CountryTag);
	}
	else
	{
		CreateEventForAI(Event, ChoicesConditionsEvaluated, CountryTag);
	}
}

void UEventInstancesController::DeleteEventWidget(UEventDescription* Event, const FName& CountryTag)
{
	if (!WidgetsInstances.Contains({Event, CountryTag})) return;

	WidgetsInstances[{Event, CountryTag}]->RemoveFromParent();

	WidgetsInstances.Remove({Event, CountryTag});
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

void UEventInstancesController::CreateEventForAI(UEventDescription* Event,
                                                 const TMap<FName, bool>& ChoicesConditionsEvaluated,
                                                 const FName& CountryTag)
{
	FiredEvents.Add({Event, CountryTag});

	const FName AISelectedChoice = FindAISelectedChoice(Event->Choices, ChoicesConditionsEvaluated);

	RegisterChoice(Event, AISelectedChoice, CountryTag);
}

void UEventInstancesController::CreateEventForPlayer(UEventDescription* Event,
                                                     const TMap<FName, bool>& ChoicesConditionsEvaluated,
                                                     const FName& CountryTag)
{
	FiredEvents.Add({Event, CountryTag});

	// TODO: Add multiplayer logic ;)

	UEventWidget* EventWidget = CreateWidget<UEventWidget>(GetWorld(), EventWidgetClass);
	EventWidget->Init(Event, CountryTag, ChoicesConditionsEvaluated);

	WidgetsInstances.Add({Event, CountryTag}, EventWidget);
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
                                               const FName& CountryTag)
{
	DeleteEventWidget(Event, CountryTag);

	for (auto& Choice : Event->Choices)
	{
		if (Choice.Name != ChoiceName) continue;
		GetGameInstance()->GetSubsystem<UOutcomesApplierSubsystem>()->ApplyOutcomes(Choice.Outcomes, CountryTag);
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
		const TArray<FName>& CountriesTags = GetCountriesForWhichEventCanBeFired(Event);

		for (auto& CountryTag : CountriesTags)
		{
			if (!ConditionsChecker->CheckConditions(Event->Conditions, CountryTag)) continue;

			TMap<FName, bool> ChoicesConditionsEvaluated;

			for (auto& Choice : Event->Choices)
			{
				bool Result = ConditionsChecker->CheckConditions(Choice.Conditions, CountryTag);
				ChoicesConditionsEvaluated.Add(Choice.Name,Result);
			}

			CreateEvent(Event, ChoicesConditionsEvaluated, CountryTag);
		}
	}
}

const TArray<FName>& UEventInstancesController::GetCountriesForWhichEventCanBeFired(UEventDescription* Event) const
{
	return Event->CountriesConditions.ForAll
		       ? GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList()
		       : Event->CountriesConditions.CountriesTags;
}
