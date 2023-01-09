#include "ProvincePopulation.h"

UProvincePopulation::UProvincePopulation()
{
	
}

UProvincePopulation::UProvincePopulation(int Population)
	: Population(Population)
{
	
}

void UProvincePopulation::Init(int ArgPopulation)
{
	this->Population = ArgPopulation;
}


int UProvincePopulation::GetPopulation()
{
	return this->Population;
}
