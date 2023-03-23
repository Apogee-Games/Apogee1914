#include "Interfaces/Ownable.h"

void IOwnable::SetCountryController(UCountry* Country)
{
	CountryController = Country;
	StrataController = nullptr;
}

void IOwnable::SetCountryOwner(UCountry* Country)
{
	CountryOwner = Country;
	StrataOwner = nullptr;
}

void IOwnable::SetStrataOwner(UStrata* Strata)
{
	StrataOwner = Strata;
	CountryOwner = nullptr;
}

void IOwnable::SetStrataController(UStrata* Strata)
{
	StrataController = Strata;
	CountryController = nullptr;
}

UCountry* IOwnable::GetCountryOwner() const
{
	return CountryOwner;
}

UCountry* IOwnable::GetCountryController() const
{
	return CountryController;
}

UStrata* IOwnable::GetStrataOwner() const
{
	return StrataOwner;
}

UStrata* IOwnable::GetStrataController() const
{
	return StrataController;
}
