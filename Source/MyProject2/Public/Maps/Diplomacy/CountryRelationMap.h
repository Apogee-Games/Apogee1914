#pragma once
#include "Scenario.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Interfaces/BaseManager.h"
#include "CountryRelationMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountryRelationMap: public UBaseManager, public IWarDeclarationObserver, public IAllianceCreationObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void SetScenario(UScenario* Scenario) override;

	void UpdateMap();

	virtual void WarWasDeclared(UWar* War) override;

	virtual void AllianceWasCreated(UAlliance* Alliance) override;

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	UTexture2D* CountryRelationMap;

	UPROPERTY(EditDefaultsOnly)
	UCountryDescription* GermanyDescription;

	FVector2d SizeVector;

	TMap<ERelationType, FColor> ColorsMapping = {
		{ERelationType::Neutral, FColor(30, 30, 30)},
		{ERelationType::NonAggressionPact, FColor(0, 30, 30)},
		{ERelationType::War, FColor(150, 10, 10)},
		{ERelationType::DefencivePact, FColor(30, 150, 30)},
		{ERelationType::Allied, FColor(30, 100, 150)}
	}; // TODO: Extract this :)

	void Clear();

	void Init(UScenario* Scenario);
};
