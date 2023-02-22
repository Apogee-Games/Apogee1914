#pragma once
#include "ProvincePopulation.generated.h"

UCLASS()
class UProvincePopulation : public UObject
{
	GENERATED_BODY()
public:
	UProvincePopulation();

	explicit UProvincePopulation(const int32 Population);

	void Init(const int32 ArgPopulation);
	
	int32 GetPopulation() const;

private:
	int32 Population;
};
