#pragma once
#include "Administration/Instances/Province.h"

class IProvinceOwningCountryObserver
{
public:
	virtual ~IProvinceOwningCountryObserver() = default;
	virtual void ProvinceHasNewOwningCountry(UProvince* Province) = 0;
};
