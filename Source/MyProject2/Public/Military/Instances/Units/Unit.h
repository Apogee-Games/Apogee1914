
#pragma once
#include "Administration/Instances/Province.h"
#include "Interfaces/Ownable.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/UnitSupplyNeeds.h"
#include "Unit.generated.h"

UENUM()
enum EMilitaryBranch
{
	Army = 0,
	Navy = 1,
	AirForce = 2
};

inline FName MilitaryBranchNames[3] = {
	"Army",
	"Navy",
	"AirForce"
};

inline EMilitaryBranch MilitaryBranches[3] = {
	Army, Navy, AirForce
};

inline int32 MilitaryBranchesNumber = 3;

//TODO: Come up with the fix for this :)

class UUnitsCollection;

UCLASS()
class UUnit: public UObject, public IOwnable
{
	GENERATED_BODY()
public:
	virtual void Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince);

	bool CanTransportUnits() const;

	// TODO: Think about transportation
	
	void Move(UProvince* Province); 

	UProvince* GetPosition() const;
	
	int32 Estimate(const TArray<TPair<UProvince*, int32>>& Path);

	int32 GetUnitTypeEquipmentRequirement(const FName& GoodName) const;

	UUnitSupplyNeeds* GetSupplyNeeds() const;

	const FName& GetUnitName() const;

	virtual EMilitaryBranch GetMilitaryBranch() const;

	void SetUnitsCollection(UUnitsCollection* ProvidedUnitsCollection);

	UUnitsCollection* GetUnitsCollection() const;

	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(UUnit* Unit);
private:
	const FUnitDescription* UnitDescription;

	UPROPERTY()
	UUnitsCollection* UnitsCollection;
	
	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	UPROPERTY()
	UUnitSupplyNeeds* SupplyNeeds;
	
	UPROPERTY()
	UProvince* Province;
};

// TODO: Add UnitMoverObserver