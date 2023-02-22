#include "ProvincePopulation.h"

UProvincePopulation::UProvincePopulation()
{
	Population = 0;
}

UProvincePopulation::UProvincePopulation(const int32 Population)
	: Population(Population)
{
	
}

void UProvincePopulation::Init(const int32 ArgPopulation)
{
	this->Population = ArgPopulation;
}


int32 UProvincePopulation::GetPopulation() const
{
	return this->Population;
}
