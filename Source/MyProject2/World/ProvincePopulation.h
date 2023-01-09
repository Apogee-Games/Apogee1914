#pragma once
#include "ProvincePopulation.generated.h"
UCLASS()
class UProvincePopulation : public UObject
{
	GENERATED_BODY()
public:
	UProvincePopulation();
	
	UProvincePopulation(int Population);

	void Init(int ArgPopulation);
	
	int GetPopulation();
	
	UPROPERTY()
	int Population;
	
};
