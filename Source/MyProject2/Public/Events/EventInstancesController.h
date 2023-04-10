#pragma once
#include "EditorSubsystem.h"
#include "Scenario.h"
#include "Administration/Instances/Country.h"
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

	void CreateEvent(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, UCountryDescription* CountryDescription);

	void DeleteEventWidget(UEventDescription* Event, UCountryDescription* CountryDescription);

	void RegisterChoice(UEventDescription* Event, const FName& ChoiceName, UCountryDescription* CountryDescription);

	void SetEventWidgetClass(const TSubclassOf<UEventWidget>& NewEventWidgetClass);

private:
	TSet<TPair<UEventDescription*, UCountryDescription*>> FiredEvents;

	UPROPERTY()
	TArray<UEventDescription*> Events;

	UPROPERTY()
	TMap<UEventDescription*, bool> ActiveEvents;
	
	TMap<TPair<UEventDescription*, UCountryDescription*>, UEventWidget*> WidgetsInstances;

	void Clear();

	void Init(UScenario* Scenario);

	void CreateEventForAI(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, UCountryDescription* CountryDescription);
	
	void CreateEventForPlayer(UEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, UCountryDescription* CountryDescription);

	static float CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated);

	FName FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated) const;

	const TArray<UCountryDescription*>& GetCountriesForWhichEventCanBeFired(UEventDescription* Event) const;
};