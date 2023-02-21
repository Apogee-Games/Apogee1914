#pragma once
#include "MyProject2/Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"
#include "MyProject2/Interfaces/FOnFullInitialization.h"
#include "MyProject2/Maps/Interfaces/Observable/CountryDistancesObservable.h"
#include "DistancesMap.generated.h"
UCLASS()
class UDistancesMap: public UWorldSubsystem, public ICountryDistancesObservable, public IProvinceOwningCountryObserver, public FOnFullInitialization
{
	GENERATED_BODY()
public:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void Init();
	
	int GetProvincesDistance(int Position) const;

	int GetStatesDistance(int Position) const;

	int GetCountriesDistance(int Position) const;

	const int* GetProvincesDistances() const;

	const int* GetStatesDistances() const;

	const int* GetCountriesDistances() const;

	virtual void Deinitialize() override;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;

private:
	int32 Depth = 15;
	
	FVector2d SizeVector;
	
	int32* ProvincesDistances = nullptr;

	int32* StatesDistances = nullptr;

	int32* CountriesDistances = nullptr;

	void CalculateDistances() const;

	FRunnableThread* CalculateProvincesDistances() const;
	
	FRunnableThread* CalculateStatesDistances() const;

	FRunnableThread* CalculateCountriesDistances() const;

	template<class T>
	FRunnableThread* GetDistanceCalculator(T* Object, bool (T::*Func)(const FColor&, const FColor&) const, int* Distance, TCHAR* Name) const
	{
		return GetDistanceCalculator(static_cast<UObject*>(Object), static_cast<bool (UObject::*)(const FColor&, const FColor&) const>(Func), Distance, Name);
	}

	FRunnableThread* GetDistanceCalculator(UObject* Object, bool (UObject::*Func)(const FColor&, const FColor&) const, int* Distance, TCHAR* Name) const;
};
