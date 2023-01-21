#include "ProvinceFactory.h"


UProvinceFactory::UProvinceFactory()
{
}

UProvinceFactory::UProvinceFactory(const FFactoryInstanceDescription& FactoryInstanceDescription, const FFactoryDescription* FactoryDescription)
	: FactoryDescription(FactoryDescription),
	Labours(FactoryInstanceDescription.Labours)
{

}

void UProvinceFactory::Produce()
{
	if(FactoryDescription == nullptr) return;
	
}

void UProvinceFactory::Init(const FFactoryInstanceDescription& FactoryInstanceDescription, const FFactoryDescription* ArgFactoryDescription)
{
	this->FactoryDescription = ArgFactoryDescription;	
	this->Labours = FactoryInstanceDescription.Labours;
}

const FFactoryDescription* UProvinceFactory::GetFactoryDescription() const
{
	return FactoryDescription;
}

int32 UProvinceFactory::GetLabours() const
{
	return Labours;
}
