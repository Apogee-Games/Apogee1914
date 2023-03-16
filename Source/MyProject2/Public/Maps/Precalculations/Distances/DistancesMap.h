#pragma once
#include "Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"
#include "Interfaces/FOnFullInitialization.h"
#include "Maps/Interfaces/Observable/CountryDistancesObservable.h"
#include "DistancesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UDistancesMap: public UWorldSubsystem, public ICountryDistancesObservable, public IProvinceOwningCountryObserver, public FOnFullInitialization
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void Init();
	
	int32 GetProvincesDistance(int32 Position) const;

	int32 GetStatesDistance(int32 Position) const;

	int32 GetCountriesDistance(int32 Position) const;

	const TArray<int32>& GetProvincesDistances() const;

	const TArray<int32>& GetStatesDistances() const;

	const TArray<int32>& GetCountriesDistances() const;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;

	UPROPERTY(EditDefaultsOnly)
	int32 Depth = 15;
private:
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
