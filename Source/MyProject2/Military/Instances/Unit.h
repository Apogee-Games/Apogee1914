
#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "Unit.generated.h"

class UUnitsRenderer;

UCLASS()
class UUnit : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FUnitDescription* ProvidedUnitDescription, UProvince* Province, const FName& CountryOwnerTag, UUnitsRenderer* UnitsRenderer);

	void Init(const FUnitDescription* ProvidedUnitDescription, UProvince* Province, const FName& CountryOwnerTag, const FName& CountryControllerTag, UUnitsRenderer* UnitsRenderer);

	bool CanTransportUnits() const;

	void AddTransportedUnit(UUnit* Unit);

	void RemoveTransportedUnit(UUnit* Unit);

	void Move(UProvince* Province);

	UProvince* GetPosition() const;
	
	int32 Estimate(const TArray<TPair<UProvince*, int32>>& Path);

	UCountry* GetCountryOwner() const;

	UCountry* GetCountryController() const;

	const TMap<FName, int32>& GetEquipmentNeeds() const;

	int32 GetUnitTypeEquipmentRequirement(const FName& GoodName) const;

	void SupplyEquipment(const FName& GoodName, int32 Amount);

	const FName& GetUnitName() const;
	
	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);
	
private:
	
	const FUnitDescription* UnitDescription;

	TSet<UUnit*> TransportedUnits; // TODO: May be extract it to another interface

	TMap<FName, int32> EquipmentNeeds;
	
	UPROPERTY()
	UProvince* Province;

	UPROPERTY()
	UUnitsRenderer* UnitsRenderer;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver