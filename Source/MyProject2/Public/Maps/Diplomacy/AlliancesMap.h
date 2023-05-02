#pragma once
#include "Scenario.h"
#include "Diplomacy/Interfaces/Observers/AllianceCreationObserver.h"
#include "Diplomacy/Interfaces/Observers/AllianceMembersObserver.h"
#include "Administration/Instances/Province.h"
#include "AlliancesMap.generated.h"


UCLASS(Abstract, Blueprintable)
class UAlliancesMap: public UGameInstanceSubsystem, public IAllianceCreationObserver, public IAllianceMembersObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FColor NonAlliedCountryColor = FColor(200, 200, 200);

	UPROPERTY(EditDefaultsOnly)
	FColor NonAlignedCountryColor;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetScenario(UScenario* Scenario);

	void UpdateMap();

	virtual void AllianceWasCreated(UAlliance* Alliance) override;
	
	virtual void CountryHasJoinedAlliance(UCountry* Country) override;

private:
	UPROPERTY()
	UTexture2D* AlliancesMapTexture;

	void Clear();

	FRunnableThread* UpdateAllianceColor(UProvince* Province, FColor* AlliancesColor) const;

	void Init(UScenario* Scenario);

};
