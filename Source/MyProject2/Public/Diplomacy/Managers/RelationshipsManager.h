#pragma once
#include "Scenario.h"
#include "Administration/Instances/Country.h"
#include "Components/ListView.h"
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

UCLASS()
class URelationshipsManager: public UGameInstanceSubsystem, public IWarDeclarationObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	bool CanDeclareWar(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	bool CanCreateAlliance(UCountry* CountryA, UCountry* CountryB);

	void SetWarRelation(UCountry* CountryA, UCountry* CountryB);
	
	void DeclareWar(UCountry* CountryA, UCountry* CountryB);

	void CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB);

	void CreateDefencivePact(UCountry* CountryA, UCountry* CountryB);

	ERelationType GetRelation(UCountry* CountryA, UCountry* CountryB);

	const TMap<UCountry*, ERelationType>& GetRelations(UCountry* Country);
private:
	TMap<UCountry*, TMap<UCountry*, ERelationType>> Relations;

	inline static int32 CanDeclareWarList = 0b00001;

	inline static int32 CanCreateNonAggressionPactList = 0b00001;

	inline static int32 CanCreateDefencivePactList = 0b00011;

	inline static int32 CanCreateAllianceList = 0b01011;

	void Clear();

	void Init(UScenario* Scenario);
};