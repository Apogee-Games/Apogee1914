
#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
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

	const TMap<FName, int32>& GetEquipmentNeeds() const;

	int32 GetUnitTypeEquipmentRequirement(const FName& GoodName) const;

	void SupplyEquipment(const FName& GoodName, int32 Amount);

	const FName& GetUnitName() const;

	virtual EMilitaryBranch GetMilitaryBranch() const;

	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(UUnit* Unit);

	// void RemoveTransportedUnit(UUnit* Unit);

	
private:
	
	const FUnitDescription* UnitDescription;

	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	TMap<FName, int32> EquipmentNeeds;

	UPROPERTY()
	UProvince* Province;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver