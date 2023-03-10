#pragma once

class UProvince;

class ICountryDistancesObserver
{
public:
	virtual ~ICountryDistancesObserver() = default;
	virtual void CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces) = 0;
};
