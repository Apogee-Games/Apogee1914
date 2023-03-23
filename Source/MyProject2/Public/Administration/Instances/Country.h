#pragma once
#include "Parliament.h"
#include "Administration/Descriptions/CountryDescription.h"
#include "Administration/Descriptions/ParliamentDescription.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Economics/Instances/Market.h"
#include "Economics/Instances/Strata.h"
#include "People/Instances/Person.h"
#include "Country.generated.h"

UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
public:
	void Init(FCountryDescription* CountryDescription, FParliamentDescription* FirstChamber, FParliamentDescription* SecondChamber);

	const FColor& GetColor() const;

	const FName& GetName() const;

	const FName& GetTag() const;

	UTexture2D* GetFlag();

	void SetIdeology(const FName& ProvidedIdeologyTag);

	UPerson* GetRuler() const;

	
	UStorage* GetStorage() const;

	TArray<UStorage*> GetStorages() const;

	
	ERelationType GetRelation(UCountry* Country);

	void SetRelation(UCountry* Country, ERelationType Relation);

	bool CanDeclareWarOn(UCountry* Country);

	bool CanCreateNonAggressionPactWith(UCountry* Country);

	bool CanCreateDefencivePactWith(UCountry* Country);

	bool CanCreateAllianceWith(UCountry* Country);

	bool MustHelpInDefenciveWar(UCountry* Country);

	bool MustHelpInAggressiveWar(UCountry* Country);

	bool CanJoinCountryWar(UCountry* Country);

	bool HasNonAggressionPactWith(UCountry* Country);

	bool HasDefencivePactWith(UCountry* Country);
	
	const TMap<UCountry*, ERelationType>& GetRelations() const;


	void SetAlliance(UAlliance* ProvidedAlliance);

	UAlliance* GetAlliance() const;

	bool IsInAlliance() const;

	
	void AddWar(UWar* War);

	void RemoveWar(UWar* War);

	const TArray<UWar*>& GetWars() const;

	bool IsCountryInWar() const;

	bool CanCountryJoinOneOfOurWars(UCountry* Country) const;

	bool IsCountryInWarWith(UCountry* Country);


	UParliament* GetFirstChamber() const;

	UParliament* GetSecondChamber() const;
private:
	FName Name;

	FName Tag;

	FColor Color;

	FName IdeologyTag;

	UPROPERTY()
	TMap<FName, FIdeologyDescription> Ideologies;
	
	UPROPERTY()
	UTexture2D* Flag = nullptr;

	UPROPERTY()
	UMarket* Market;
	
	UPROPERTY()
	UStrata* LowerStrata;
	
	UPROPERTY()
	UStrata* MiddleStrata;
	
	UPROPERTY()
	UStrata* UpperStrata;

	UPROPERTY()
	UStorage* Storage;

	UPROPERTY()
	UPerson* Ruler;

	UPROPERTY()
	UAlliance* Alliance;

	TMap<UCountry*, ERelationType> Relations;

	UPROPERTY()
	TArray<UWar*> Wars;

	UPROPERTY()
	UParliament* FirstChamberParliament;

	UPROPERTY()
	UParliament* SecondChamberParliament;
	
	void InitStrata();

	void LoadFlag();

	inline static int32 CanDeclareWarList = 0b00001;
	inline static int32 CanCreateNonAggressionPactList = 0b00001;
	inline static int32 CanCreateDefencivePactList = 0b00011;
	inline static int32 CanCreateAllianceList = 0b01011;
	inline static int32 MustHelpInDefenciveWarList = 0b11000;
	inline static int32 MustHelpInAggressiveWarList = 0b10000;
	inline static int32 CanJoinCountriesWarList = 0b10000;
};
