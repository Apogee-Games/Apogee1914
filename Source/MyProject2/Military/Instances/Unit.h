
#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "Unit.generated.h"

class UUnitsRenderer;

UCLASS()
class UUnit : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FUnitDescription* UnitDescription, const FColor& ProvinceColor, FString CountryOwnerTag, UUnitsRenderer* UnitsRenderer);

	void Init(const FUnitDescription* UnitDescription, const FColor& ProvinceColor, FString CountryOwnerTag, FString CountryControllerTag, UUnitsRenderer* UnitsRenderer);

	bool CanTransportUnits() const;

	void AddTransportedUnit(UUnit* Unit);

	void RemoveTransportedUnit(UUnit* Unit);

	void Move(FColor NewProvinceColor);

	FColor GetPosition() const;
	
	int Estimate(const TArray<TPair<FColor, int>>& Path);

	UCountry* GetCountryOwner() const;

	UCountry* GetCountryController() const;
	
	// bool CanAccessProvince(UProvince* Province);

	// FString GetProvinceAccessType(UProvince* Province);
	
private:
	bool bCanTransportUnits;
	
	TSet<UUnit*> TransportedUnits;

	FColor ProvinceColor;

	TArray<FString> CanAccessProvinceTypes;

	UPROPERTY()
	UUnitsRenderer* UnitsRenderer;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UCountry* CountryController;
};

// TODO: Add UnitMoverObserver