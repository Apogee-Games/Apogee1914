
#pragma once
#include "Administration/Instances/Province.h"
#include "Interfaces/Ownable.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/UnitSupplyNeeds.h"
#include "Unit.generated.h"

UENUM()
enum class EMilitaryBranch
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

	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(UUnit* Unit);
private:
	const FUnitDescription* UnitDescription;

	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	UPROPERTY()
	UUnitSupplyNeeds* SupplyNeeds;
	
	UPROPERTY()
	UProvince* Province;
};

// TODO: Add UnitMoverObserver