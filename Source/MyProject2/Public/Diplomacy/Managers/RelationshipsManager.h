#pragma once
#include "Interfaces/BaseManager.h"

#include "RelationshipsManager.generated.h"

class UCountry;
class UAlliance;
class UWar;

UENUM()
enum class ERelationType: int8 { 
	Neutral = 1,
	NonAggressionPact = 2,
	War = 4,
	DefencivePact = 8,
	Allied = 16
};

UENUM()
enum class EAllianceMemberStatus
{
	Joining,
	Leaving
};


UENUM()
enum class EAlliancesStatus
{
	Created,
	Dissolved
};

UENUM()
enum class EWarStatus
{
	Declared,
	Ended
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAllianceStatusChanged, UAlliance*, EAlliancesStatus)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWarStatusChanged, UWar*, EWarStatus) 

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAllianceMemberStatusChanged, UAlliance*, UCountry*, EAllianceMemberStatus)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCountryRelationsTypeChanged, UCountry*, UCountry*, ERelationType)


UCLASS(Abstract, Blueprintable)
class URelationshipsManager: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	void DeclareWar(UCountry* CountryA, UCountry* CountryB);
	void CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries = {});

	virtual ELoadStage GetLoadStage() override;

	FOnAllianceStatusChanged OnAllianceStatusChanged;
	FOnWarStatusChanged OnWarStatusChanged;
	
	FOnAllianceMemberStatusChanged OnAllianceMemberStatusChanged;
	FOnCountryRelationsTypeChanged OnCountryRelationsTypeChanged;
private:
	void Clear();

	void Init(UScenario* Scenario);
};
