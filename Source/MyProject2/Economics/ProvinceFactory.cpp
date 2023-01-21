#include "ProvinceFactory.h"

UProvinceFactory::UProvinceFactory()
{
}

void UProvinceFactory::Init(const FFactoryDescription* ArgFactoryType)
{
	this->FactoryDescription = ArgFactoryType;
	this->Labours = 0;
}

void UProvinceFactory::Produce()
{
	if(FactoryDescription == nullptr) return;
	
}