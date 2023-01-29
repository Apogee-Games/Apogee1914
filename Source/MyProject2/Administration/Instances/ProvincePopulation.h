#pragma once
#include "ProvincePopulation.generated.h"

UCLASS()
class UProvincePopulation : public UObject
{
	GENERATED_BODY()
public:
	UProvincePopulation();

	explicit UProvincePopulation(const int Population);

	void Init(const int ArgPopulation);
	
	int GetPopulation() const;

private:
	UPROPERTY()
	int Population;
	
};
