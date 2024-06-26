
#pragma once
#include "Administration/Instances/Province.h"
#include "Interfaces/Ownable.h"
#include "Maps/Graph.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/UnitSupplyNeeds.h"
#include "Unit.generated.h"

//TODO: Come up with the fix for this :)

class UUnitsCollection;

UCLASS()
class UUnit: public UObject, public IOwnable
{
	GENERATED_BODY()
public:
	virtual void Init(UUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince);
	void Dissolve();
	
	bool CanTransportUnits() const;

	// TODO: Think about transportation
	
	void Move(UProvince* Province); 

	UProvince* GetPosition() const;
	
	int32 Estimate(const TArray<FPathElement>& Path);

	int32 GetUnitTypeEquipmentRequirement(UGoodDescription* Good) const;

	UUnitSupplyNeeds* GetSupplyNeeds() const;

	const FName& GetUnitName() const;

	UMilitaryBranchDescription* GetMilitaryBranch() const;

	void SetUnitsCollection(UUnitsCollection* ProvidedUnitsCollection);

	UUnitsCollection* GetUnitsCollection() const;

	float GetAttackScore();

	float GetDefenceScore();
	
	float Damage(float DamageScore);

	float GetManpower() const;

	void SetIsUnitMoving(bool InbIsUnitMoving);
	bool IsUnitMoving() const;
	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);

	// void AddTransportedUnit(UUnit* Unit);
private:
	UPROPERTY()
	UUnitDescription* UnitDescription;

	UPROPERTY()
	UUnitsCollection* UnitsCollection;
	
	//TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	UPROPERTY()
	UUnitSupplyNeeds* SupplyNeeds;
	
	UPROPERTY()
	UProvince* Province;

	bool bIsUnitMoving = false;
	
	float Manpower;

	float Training = 0;
};

// TODO: Add UnitMoverObserver