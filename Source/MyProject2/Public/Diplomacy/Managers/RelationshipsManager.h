#pragma once
#include "Scenario.h"
#include "Components/ListView.h"
#include "Diplomacy/Interfaces/Observables/AllianceCreationObservable.h"
#include "Diplomacy/Interfaces/Observables/WarDeclarationObservable.h"
#include "Diplomacy/Interfaces/Observables/AllianceMembersObservable.h"
#include "Widgets/Diplomacy/Menu/DiplomaticPactsWidgets.h"

#include "RelationshipsManager.generated.h"

UENUM()
enum ERelationType { 
	Neutral = 1,
	NonAggressionPact = 2,
	War = 4,
	DefencivePact = 8,
	Allied = 16
};

class UCountry;

UCLASS(Abstract, Blueprintable)
class URelationshipsManager: public UGameInstanceSubsystem, public IWarDeclarationObservable, public IAllianceCreationObservable, public IAllianceMembersObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	void DeclareWar(UCountry* CountryA, UCountry* CountryB);

	void CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void BreakNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void CreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	void BreakDefencivePact(UCountry* CountryA, UCountry* CountryB);

	void CreateAlliance(UCountry* Country, const FText& AllianceName);

	void CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries);

private:
	void Clear();

	void Init(UScenario* Scenario);
};
