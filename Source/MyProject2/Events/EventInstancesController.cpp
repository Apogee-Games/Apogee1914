#include "EventInstancesController.h"
#include "OutcomeAppliers/Headers/EventsOutcomesApplier.h"
#include "ConditionCheckers/Headers/EventContitionsChecker.h"
#include "MyProject2/InGameTime.h"
#include "UObject/UObjectGlobals.h"
#include "MyProject2/MyGameInstance.h"
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"


void UEventInstancesController::CreateEvent(const FString& EventName, const FEventDescription* Event,
                                            const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                            const FString& CountryTag)
{
	if (WidgetsInstances.Contains({EventName, CountryTag})) return; // Event is already created
	if (Event->TriggerOnce && FiredEvents.Contains({EventName, CountryTag})) return;
	if (static_cast<UMyGameInstance*>(GetWorld()->GetGameInstance())->IsCountryRuledByPlayer(CountryTag))
		CreateEventForPlayer(EventName, Event, ChoicesConditionsEvaluated, CountryTag);
	else CreateEventForAI(EventName, Event, ChoicesConditionsEvaluated, CountryTag);
}

void UEventInstancesController::DeleteEventWidget(const FString& EventName, const FString& CountryTag)
{
	if (!WidgetsInstances.Contains({EventName, CountryTag})) return; // Can't delete what doesn't exist

	WidgetsInstances[{EventName, CountryTag}]->RemoveFromParent(); // Remove from player screen

	WidgetsInstances.Remove({EventName, CountryTag});
	// Delete the only pointer to widget, so that it can be garbage collected
}

void UEventInstancesController::CreateEventForAI(const FString& EventName, const FEventDescription* Event,
                                                 const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                                 const FString& CountryTag)
{
	FiredEvents.Add({EventName, CountryTag}); // Added this event to history of all events

	const FString AISelectedChoice = FindAISelectedChoice(Event->Choices, ChoicesConditionsEvaluated);

	RegisterChoice(EventName, AISelectedChoice, CountryTag);
}

void UEventInstancesController::CreateEventForPlayer(const FString& EventName, const FEventDescription* Event,
                                                     const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                                     const FString& CountryTag)
{
	FiredEvents.Add({EventName, CountryTag}); // Added this event to history of all events

	UEventWidget* EventWidget = CreateWidget<UEventWidget>(GetWorld(), EventWidgetClass);
	EventWidget->Init(Event->Title, Event->Text, Event->ImagePath);

	// Adding all choices that have their condition meet
	for (const auto& Choice : Event->Choices)
	{
		if (ChoicesConditionsEvaluated[Choice.Name])
		{
			EventWidget->AddChoice(EventName, Choice.Text, CountryTag, Choice.Text);
		}
	}

	WidgetsInstances.Add({EventName, CountryTag}, EventWidget);
	EventWidget->AddToViewport();
}

inline float UEventInstancesController::CalculateSumOfAIChancesForChoices(
	const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated)
{
	float SummedChance = 0;
	for (const auto& Choice : Choices)
	{
		if (!ChoicesConditionsEvaluated[Choice.Name]) continue;
		SummedChance += Choice.AIChance;
	}
	return SummedChance;
}

FString UEventInstancesController::FindAISelectedChoice(const TArray<FEventChoice>& Choices,
                                                        const TMap<FString, bool>& ChoicesConditionsEvaluated) const
{
	// Use Geometrical Probability to find which choice to select
	const float SummedChance = CalculateSumOfAIChancesForChoices(Choices, ChoicesConditionsEvaluated);

	FString SelectedChoice;

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
		this->Events.Add(Pair.Key.ToString(), reinterpret_cast<FEventDescription*>(Pair.Value));
	}
}

void UEventInstancesController::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	EventWidgetClass = GetWorld()->GetGameState<AMyGameState>()->EventWidgetClass;
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UEventInstancesController::CheckEvents, FTimespan(1, 0 , 0, 0));
}

void UEventInstancesController::RegisterChoice(const FString& EventName, const FString& ChoiceName,
                                               const FString& CountryTag)
{
	// Removing Event widget
	DeleteEventWidget(EventName, CountryTag);

	// Applying selected choice outcomes
	for (auto& Choice : Events[EventName]->Choices)
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
	for (const auto& Pair : Events)
	{
		TArray<FString>* CountriesTags = GetCountriesForWhichEventCanBeFired(Pair.Value);

		for (auto& CountryTag : *CountriesTags)
		{
			if (!ConditionsChecker->CheckConditions(Pair.Value->Conditions, CountryTag)) continue;
			// Skip current event because conditions are not meet 

			TMap<FString, bool> ChoicesConditionsEvaluated; // Holds results for choice condition check

			for (auto& Choice : Pair.Value->Choices)
			{
				ChoicesConditionsEvaluated.Add(Choice.Name,
				                               ConditionsChecker->CheckConditions(Choice.Conditions, CountryTag));
			}

			CreateEvent(Pair.Key, Pair.Value, ChoicesConditionsEvaluated, CountryTag);
		}
	}
}


TArray<FString>* UEventInstancesController::GetCountriesForWhichEventCanBeFired(FEventDescription* Event) const
{
	return Event->CountriesConditions.ForAll
		       ? GetWorld()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList()
		       : &Event->CountriesConditions.CountriesTags;
}
