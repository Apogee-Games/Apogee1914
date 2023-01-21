#include "ProvinceFactory.h"

UProvinceFactory::UProvinceFactory()
{
}

void UProvinceFactory::Init(const FProvince* ArgProvince, const FFactoryDescription* ArgFactoryType)
{
	this->Province = ArgProvince;
	this->FactoryDescription = ArgFactoryType;
	this->Labours = 0;
}

void UProvinceFactory::Produce()
{
	if(Province == nullptr || FactoryDescription == nullptr) return;
	
	std::cout << "Labors: " << Labours << std::endl;
	std::cout << "Population: " << Province->Population << std::endl;
	for(auto &[GoodID, Amount] : FactoryDescription->GoodOutput)
	{
		std::cout << Amount << " - Good \n";
	}
}