#pragma once
#include "EditorSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "EventDescription/EventDescription.h"
#include "MyProject2/Widgets/EventWidget.h"
#include "EventInstancesController.generated.h"

/**
 * Class used to control all events instances
 */
UCLASS()
class UEventInstancesController: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void Tick(float DeltaTime);
	
	void CheckEvents();

	/**
	 * Creates and displays event widget with required data
	 */
	void CreateEvent(const FName& EventName, const FEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);

	/**
	 *	Removes event widget 
	 */
	void DeleteEventWidget(const FName& EventName, const FName& CountryTag);

	/**
	 *	Method used to record selected choice for specific event
	 */
	void RegisterChoice(const FName& EventName, const FName& ChoiceName, const FName& CountryTag);

	void SetEventWidgetClass(const TSubclassOf<UEventWidget>& NewEventWidgetClass);

private:
	TSubclassOf<UEventWidget> EventWidgetClass;

	TSet<TPair<FName, FName>> FiredEvents;

	TMap<FName, FEventDescription*> Events;

	TMap<FName, bool> ActiveEvents;
	
	TMap<TPair<FName, FName>, UEventWidget*> WidgetsInstances;

	void CreateEventForAI(const FName& EventName, const FEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);
	
	void CreateEventForPlayer(const FName& EventName, const FEventDescription* Event, const TMap<FName, bool>& ChoicesConditionsEvaluated, const FName& CountryTag);

	static float CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated);

	FName FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FName, bool>& ChoicesConditionsEvaluated) const;

	const TArray<FName>& GetCountriesForWhichEventCanBeFired(FEventDescription* Event) const;
};