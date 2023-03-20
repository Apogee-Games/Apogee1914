#pragma once
#include "Scenario.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "CountryRelationMap.generated.h"

UCLASS()
class UCountryRelationMap: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	void UpdateMap();

private:
	UPROPERTY()
	UTexture2D* CountryRelationMap;

	FVector2d SizeVector;

	TMap<ERelationType, FColor> ColorsMapping = {
		{ERelationType::Neutral, FColor(30, 30, 30)},
		{ERelationType::NonAggressionPact, FColor(0, 30, 30)},
		{ERelationType::War, FColor(150, 10, 10)},
		{ERelationType::DefencivePact, FColor(30, 150, 30)},
		{ERelationType::Allied, FColor(30, 100, 150)}
	};

	void Clear();

	void Init(UScenario* Scenario);
};
