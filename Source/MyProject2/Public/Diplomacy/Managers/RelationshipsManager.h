#pragma once
#include "Scenario.h"
#include "Administration/Instances/Country.h"
#include "Components/ListView.h"
#include "Diplomacy/Interfaces/Observables/AllianceCreationObservable.h"
#include "Diplomacy/Interfaces/Observables/WarDeclarationObservable.h"

#include "RelationshipsManager.generated.h"

UENUM()
enum ERelationType { 
	Neutral = 1,
	NonAggressionPact = 2,
	War = 4,
	DefencivePact = 8,
	Allied = 16
};

UCLASS(Abstract, Blueprintable)
class URelationshipsManager: public UGameInstanceSubsystem, public IWarDeclarationObservable, public IAllianceCreationObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	bool CanDeclareWar(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateAlliance(UCountry* CountryA, UCountry* CountryB);

	void SetRelation(UCountry* CountryA, UCountry* CountryB, ERelationType Relation);
	
	void DeclareWar(UCountry* CountryA, UCountry* CountryB);

	void CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void CreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	void CreateAlliance(UCountry* Country, const FText& AllianceName);

	void CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries);
	
	ERelationType GetRelation(UCountry* CountryA, UCountry* CountryB);

	const TMap<UCountry*, ERelationType>& GetRelations(UCountry* Country);

	const TArray<UWar*>& GetCountryWars(UCountry* Country);

	bool IsCountryInWar(UCountry* Country);

	bool CanCountryJoinWar(UCountry* CountryA, UCountry* CountryB);
	
	bool IsTherePossibleWarToJoin(UCountry* CountryToJoin, UCountry* CountryToJoinTo);
private:
	TMap<UCountry*, TMap<UCountry*, ERelationType>> Relations;

	TMap<UCountry*, TArray<UWar*>> CountriesWars;

	inline static int32 CanDeclareWarList = 0b00001;

	inline static int32 CanCreateNonAggressionPactList = 0b00001;

	inline static int32 CanCreateDefencivePactList = 0b00011;

	inline static int32 CanCreateAllianceList = 0b01011;

	inline static int32 MustComeToDefense = 0b11000;

	inline static int32 MustHelpInAggressiveWar = 0b10000;

	inline static int32 CanJoinWar = 0b10000;

	void Clear();

	void Init(UScenario* Scenario);
};
