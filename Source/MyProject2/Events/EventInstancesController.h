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
	void CreateEvent(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);

	/**
	 *	Removes event widget 
	 */
	void DeleteEventWidget(const FString& EventName, const FString& CountryTag);

	/**
	 *	Method used to record selected choice for specific event
	 */
	void RegisterChoice(const FString& EventName, const FString& ChoiceName, const FString& CountryTag);

	void SetEventWidgetClass(const TSubclassOf<UEventWidget>& NewEventWidgetClass);

private:
	TSubclassOf<UEventWidget> EventWidgetClass;

	TSet<TPair<FString, FString>> FiredEvents;

	TMap<FString, FEventDescription*> Events;

	TMap<FString, bool> ActiveEvents;
	
	TMap<TPair<FString, FString>, UEventWidget*> WidgetsInstances;

	void CreateEventForAI(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);
	
	void CreateEventForPlayer(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);

	static float CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated);

	FString FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated) const;

	const TArray<FString>& GetCountriesForWhichEventCanBeFired(FEventDescription* Event) const;
};