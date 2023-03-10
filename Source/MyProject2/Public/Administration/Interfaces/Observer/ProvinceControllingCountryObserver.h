#pragma once
#include "Administration/Instances/Province.h"

class IProvinceControllingCountryObserver
{
public:
	virtual ~IProvinceControllingCountryObserver() = default;
	virtual void ProvinceHasNewControllingCountry(UProvince* Province) = 0;
};
