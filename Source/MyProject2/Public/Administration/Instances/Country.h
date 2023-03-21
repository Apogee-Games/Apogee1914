#pragma once
#include "Administration/Descriptions/CountryDescription.h"
#include "Economics/Instances/Market.h"
#include "Economics/Instances/Strata.h"
#include "People/Instances/Person.h"

#include "Country.generated.h"

class UAlliance;
UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
public:
	void Init(FCountryDescription* CountryDescription);

	const FColor& GetColor() const;

	const FName& GetName() const;

	const FName& GetTag() const;

	UTexture2D* GetFlag();

	UStorage* GetStorage() const;

	void SetRulingFraction(const FName& ProvidedRulingFractionTag);

	UPerson* GetRuler() const;

	TArray<UStorage*> GetStorages() const;

	void SetAlliance(UAlliance* ProvidedAlliance);

	UAlliance* GetAlliance() const;
private:
	FName Name;

	FName Tag;

	FColor Color;

	FName RulingFractionTag;

	UPROPERTY()
	TMap<FName, FFractionDescription> Fractions;
	
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
	
	void InitStrata();

	void LoadFlag();
};
