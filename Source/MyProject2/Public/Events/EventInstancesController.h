#pragma once
#include "EditorSubsystem.h"
#include "Scenario.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Description/EventDescription.h"
#include "Widgets/Events/EventWidget.h"
#include "EventInstancesController.generated.h"

/**
 * Class used to control all events instances
 */
UCLASS(Abstract, Blueprintable)
class UEventInstancesController: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEventWidget> EventWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MinDeltaBetweenEventChecks = FTimespan(24, 0, 0);

	void SetScenario(UScenario* Scenario);
	
	virtual void Tick(float DeltaTime);
	
	void CheckEvents();

	void CreateEvent(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);

	void DeleteEventWidget(UEventDescription* Event, const FName& CountryTag);

	void RegisterChoice(UEventDescription* Event, const FName& ChoiceName, const FName& CountryTag);

	void SetEventWidgetClass(const TSubclassOf<UEventWidget>& NewEventWidgetClass);

private:
	TSet<TPair<UEventDescription*, FName>> FiredEvents;

	UPROPERTY()
	TArray<UEventDescription*> Events;

	UPROPERTY()
	TMap<UEventDescription*, bool> ActiveEvents;
	
	TMap<TPair<UEventDescription*, FName>, UEventWidget*> WidgetsInstances;

	void Clear();

	void Init(UScenario* Scenario);

	void CreateEventForAI(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);
	
	void CreateEventForPlayer(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);

	static float CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated);

	FName FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated) const;

	const TArray<FName>& GetCountriesForWhichEventCanBeFired(UEventDescription* Event) const;
};