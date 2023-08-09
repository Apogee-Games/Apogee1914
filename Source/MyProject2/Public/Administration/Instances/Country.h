#pragma once
#include "Parliament.h"
#include "Province.h"
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
	void Init(UCountryDescription* ProvidedCountryDescription);

	UCountryDescription* GetId() const;
	
	const FColor& GetColor() const;

	const FText& GetName() const;

	const FName& GetTag() const;

	UTexture2D* GetFlag();

	void SetIdeology(UIdeologyDescription* ProvidedIdeology);

	UPerson* GetRuler() const;

	
	UStorage* GetStorage() const;

	TArray<UStorage*> GetStorages() const;

	
	ERelationType GetRelation(UCountry* Country);

	void SetRelation(UCountry* Country, ERelationType Relation);
	
	bool CanCreateNonAggressionPactWith(UCountry* Country);
	bool CreateNonAggressionPactWith(UCountry* Country);
	void BreakNonAggressionPactWith(UCountry* Country);

	bool CanCreateDefencivePactWith(UCountry* Country);
	bool CreateDefencivePactWith(UCountry* Country);
	void BreakDefencivePactWith(UCountry* Country);
	
	bool CanDeclareWarOn(UCountry* Country);
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

	bool IsInWar() const;

	bool CanCountryJoinOneOfOurWars(UCountry* Country) const;

	bool IsInWarWith(UCountry* Country);


	UParliament* GetFirstChamber() const;

	UParliament* GetSecondChamber() const;

	UIdeologyDescription* GetIdeology() const;

	void SetIsNonAligned(bool IsNonAligned);

	bool IsNonAligned() const;

	void AddProvince(UProvince* Province);

	void RemoveProvince(UProvince* Province);

	const TArray<UProvince*>& GetProvinces() const;
private:
	UPROPERTY()
	UCountryDescription* CountryDescription;
	
	FName Name;

	FName Tag;

	FColor Color;

	UPROPERTY()
	UIdeologyDescription* Ideology;

	UPROPERTY()
	TMap<UIdeologyDescription*, FCountryIdeologyParameters> IdeologiesParameters;
	
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

	UPROPERTY()
	TArray<UProvince*> Provinces;

	bool bIsNonAligned = false;
	
	void InitStrata();

	inline static int32 CanDeclareWarList = 0b00001;
	inline static int32 CanCreateNonAggressionPactList = 0b00001;
	inline static int32 CanCreateDefencivePactList = 0b00011;
	inline static int32 CanCreateAllianceList = 0b01011;
	inline static int32 MustHelpInDefenciveWarList = 0b11000;
	inline static int32 MustHelpInAggressiveWarList = 0b10000;
	inline static int32 CanJoinCountriesWarList = 0b10000;
};
