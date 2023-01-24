#include "ProvincePopulation.h"

UProvincePopulation::UProvincePopulation()
{
	Population = 0;
}

UProvincePopulation::UProvincePopulation(const int Population)
	: Population(Population)
{
	
}

void UProvincePopulation::Init(const int ArgPopulation)
{
	this->Population = ArgPopulation;
}


int UProvincePopulation::GetPopulation() const
{
	return this->Population;
}
