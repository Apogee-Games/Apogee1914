#include "EventInstancesController.h"
#include "OutcomeAppliers/Headers/EventsOutcomesApplier.h"
#include "ConditionCheckers/Headers/EventContitionsChecker.h"
#include "MyProject2/InGameTime.h"
#include "UObject/UObjectGlobals.h"
#include "MyProject2/MyGameInstance.h"
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"


void UEventInstancesController::CreateEvent(FEventDescription* Event,
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

void UEventInstancesController::DeleteEventWidget(FEventDescription* Event, const FName& CountryTag)
{
	if (!WidgetsInstances.Contains({Event, CountryTag})) return;

	WidgetsInstances[{Event, CountryTag}]->RemoveFromParent();

	WidgetsInstances.Remove({Event, CountryTag});
}

void UEventInstancesController::CreateEventForAI(FEventDescription* Event,
                                                 const TMap<FName, bool>& ChoicesConditionsEvaluated,
                                                 const FName& CountryTag)
{
	FiredEvents.Add({Event, CountryTag});

	const FName AISelectedChoice = FindAISelectedChoice(Event->Choices, ChoicesConditionsEvaluated);

	RegisterChoice(Event, AISelectedChoice, CountryTag);
}

void UEventInstancesController::CreateEventForPlayer(FEventDescription* Event,
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

void UEventInstancesController::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UDataTable* EventsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/events_description"));

	for (const auto Pair : EventsDataTable->GetRowMap())
	{
		Events.Add(reinterpret_cast<FEventDescription*>(Pair.Value));
	}
}

void UEventInstancesController::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UEventInstancesController::CheckEvents,
	                                                          MinDeltaBetweenEventChecks);
}

void UEventInstancesController::RegisterChoice(FEventDescription* Event, const FName& ChoiceName,
                                               const FName& CountryTag)
{
	DeleteEventWidget(Event, CountryTag);

	for (auto& Choice : Event->Choices)
	{
		if (Choice.Name != ChoiceName) continue;
		GetWorld()->GetSubsystem<UEventsOutcomesApplier>()->ApplyOutcomes(Choice.Outcomes, CountryTag);
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
	UEventConditionsChecker* ConditionsChecker = GetWorld()->GetSubsystem<UEventConditionsChecker>();
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

const TArray<FName>& UEventInstancesController::GetCountriesForWhichEventCanBeFired(FEventDescription* Event) const
{
	return Event->CountriesConditions.ForAll
		       ? GetWorld()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList()
		       : Event->CountriesConditions.CountriesTags;
}
