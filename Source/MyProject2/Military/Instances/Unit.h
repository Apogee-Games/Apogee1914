
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
	void Init(const FUnitDescription* UnitDescription, UProvince* Province, FName CountryOwnerTag, UUnitsRenderer* UnitsRenderer);

	//TODO: Const References ?
	void Init(const FUnitDescription* UnitDescription, UProvince* Province, FName CountryOwnerTag, FName CountryControllerTag, UUnitsRenderer* UnitsRenderer);

	bool CanTransportUnits() const;

	void AddTransportedUnit(UUnit* Unit);

	void RemoveTransportedUnit(UUnit* Unit);

	void Move(UProvince* Province);

	UProvince* GetPosition() const;
	
	int Estimate(const TArray<TPair<UProvince*, int>>& Path);

	UCountry* GetCountryOwner() const;

	UCountry* GetCountryController() const;
	
	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);
	
private:
	bool bCanTransportUnits;
	
	TSet<UUnit*> TransportedUnits;

	UPROPERTY()
	UProvince* Province;

	TArray<FName> CanAccessProvinceTypes;

	UPROPERTY()
	UUnitsRenderer* UnitsRenderer;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver