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

	const TArray<int32>& GetProvincesDistances() const;

	const TArray<int32>& GetStatesDistances() const;

	const TArray<int32>& GetCountriesDistances() const;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;

private:
	int32 Depth = 15;
	
	FVector2d SizeVector;
	
	TArray<int32> ProvincesDistances;

	TArray<int32> StatesDistances;

	TArray<int32> CountriesDistances;

	void CalculateDistances();

	FRunnableThread* CalculateProvincesDistances();
	
	FRunnableThread* CalculateStatesDistances();

	FRunnableThread* CalculateCountriesDistances();

	template<class T>
	FRunnableThread* GetDistanceCalculator(T* Object, bool (T::*Func)(const FColor&, const FColor&) const, TArray<int32>& Distance, TCHAR* Name)
	{
		return GetDistanceCalculator(static_cast<UObject*>(Object), static_cast<bool (UObject::*)(const FColor&, const FColor&) const>(Func), Distance, Name);
	}

	FRunnableThread* GetDistanceCalculator(UObject* Object, bool (UObject::*Func)(const FColor&, const FColor&) const, TArray<int32>& Distance, TCHAR* Name);
};
