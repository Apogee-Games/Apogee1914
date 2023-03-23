#pragma once
#include "Scenario.h"
#include "Diplomacy/Interfaces/Observers/AllianceCreationObserver.h"
#include "AlliancesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UAlliancesMap: public UGameInstanceSubsystem, public IAllianceCreationObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FColor NonAlliedCountryColor = FColor(200, 200, 200);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetScenario(UScenario* Scenario);

	void UpdateMap();

	virtual void AllianceWasCreated(UAlliance* Alliance) override;
private:
	UPROPERTY()
	UTexture2D* AlliancesMapTexture;

	void Clear();

	void Init(UScenario* Scenario);
};
