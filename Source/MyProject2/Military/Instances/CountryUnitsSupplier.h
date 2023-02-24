#pragma once
#include "Unit.h"
#include "MyProject2/Economics/Instances/Public/Storage.h"

#include "CountryUnitsSupplier.generated.h"

UCLASS()
class UCountryUnitsSupplier: public UObject
{
	GENERATED_BODY()	
public:

	void Init(UStorage* ProvidedStorage);

	void Supply();

	void AddUnit(UUnit* Unit);
	
private:
	UPROPERTY()
	UStorage* Storage;

	UPROPERTY()
	TArray<UUnit*> Units;

	void Supply(UUnit* Unit);
};
