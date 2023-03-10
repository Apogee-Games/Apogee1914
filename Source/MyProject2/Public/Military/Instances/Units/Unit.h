
#pragma once
#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/UnitSupplyNeeds.h"
#include "Unit.generated.h"

enum class EMilitaryBranch
{
	Army,
	Navy,
	AirForce
};

UCLASS()
class UUnit: public UObject
{
	GENERATED_BODY()
public:
	virtual void Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, UCountry* ProvidedCountryOwner);
	
	virtual void Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, UCountry* ProvidedCountryOwner, UCountry* ProvidedCountryController);

	bool CanTransportUnits() const;

	// TODO: Think about transportation
	
	void Move(UProvince* Province); 

	UProvince* GetPosition() const;
	
	int32 Estimate(const TArray<TPair<UProvince*, int32>>& Path);

	UCountry* GetCountryOwner() const;

	UCountry* GetCountryController() const;

	int32 GetUnitTypeEquipmentRequirement(const FName& GoodName) const;

	UUnitSupplyNeeds* GetSupplyNeeds() const;

	const FName& GetUnitName() const;

	virtual EMilitaryBranch GetMilitaryBranch() const;

	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(UUnit* Unit);

	// void RemoveTransportedUnit(UUnit* Unit);
	
private:
	
	const FUnitDescription* UnitDescription;

	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	UPROPERTY()
	UUnitSupplyNeeds* SupplyNeeds;
	
	UPROPERTY()
	UProvince* Province;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver