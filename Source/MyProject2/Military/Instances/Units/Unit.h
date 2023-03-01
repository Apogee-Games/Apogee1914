
#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"

enum class EMilitaryBranch
{
	Army,
	Navy,
	AirForce
};

class FUnit
{
public:
	FUnit(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner);
	
	FUnit(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController);

	bool CanTransportUnits() const;

	// TODO: Think about transportation
	
	void Move(UProvince* Province); 

	UProvince* GetPosition() const;
	
	int32 Estimate(const TArray<TPair<UProvince*, int32>>& Path);

	UCountry* GetCountryOwner() const;

	UCountry* GetCountryController() const;

	const TMap<FName, int32>& GetEquipmentNeeds() const;

	int32 GetUnitTypeEquipmentRequirement(const FName& GoodName) const;

	void SupplyEquipment(const FName& GoodName, int32 Amount);

	const FName& GetUnitName() const;

	virtual EMilitaryBranch GetMilitaryBranch() const = 0;

	virtual ~FUnit() = default;
	
	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(FUnit* Unit);

	// void RemoveTransportedUnit(FUnit* Unit);

	
private:
	
	const FUnitDescription* UnitDescription;

	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	TMap<FName, int32> EquipmentNeeds;
	
	UProvince* Province;

	UCountry* CountryOwner;

	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver