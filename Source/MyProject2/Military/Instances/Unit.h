
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
	void Init(const FUnitDescription* UnitDescription, UProvince* Province, FString CountryOwnerTag, UUnitsRenderer* UnitsRenderer);

	void Init(const FUnitDescription* UnitDescription, UProvince* Province, FString CountryOwnerTag, FString CountryControllerTag, UUnitsRenderer* UnitsRenderer);

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

	TArray<FString> CanAccessProvinceTypes;

	UPROPERTY()
	UUnitsRenderer* UnitsRenderer;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver