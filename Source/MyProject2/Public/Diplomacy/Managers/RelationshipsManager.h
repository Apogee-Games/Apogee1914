#pragma once
#include "Diplomacy/Interfaces/Observables/AllianceCreationObservable.h"
#include "Diplomacy/Interfaces/Observables/WarDeclarationObservable.h"
#include "Diplomacy/Interfaces/Observables/AllianceMembersObservable.h"
#include "Interfaces/BaseManager.h"

#include "RelationshipsManager.generated.h"

UENUM()
enum class ERelationType: int8 { 
	Neutral = 1,
	NonAggressionPact = 2,
	War = 4,
	DefencivePact = 8,
	Allied = 16
};

class UCountry;

UCLASS(Abstract, Blueprintable)
class URelationshipsManager: public UBaseManager, public IWarDeclarationObservable, public IAllianceCreationObservable, public IAllianceMembersObservable
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	void DeclareWar(UCountry* CountryA, UCountry* CountryB);

	void CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void BreakNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void CreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	void BreakDefencivePact(UCountry* CountryA, UCountry* CountryB);

	void CreateAlliance(UCountry* Country, const FText& AllianceName);

	void CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries);

	virtual ELoadStage GetLoadStage() override;
private:
	void Clear();

	void Init(UScenario* Scenario);
};
