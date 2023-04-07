#pragma once

class UCountry;
class UStrata;

class IOwnable
{
public:
	IOwnable() = default;
	
	virtual void SetCountryController(UCountry* Country);

	virtual void SetCountryOwner(UCountry* Country);

	virtual void SetStrataOwner(UStrata* Strata);
	
	virtual void SetStrataController(UStrata* Strata);
	
	virtual UCountry* GetCountryOwner() const;

	virtual UCountry* GetCountryController() const;

	virtual UStrata* GetStrataOwner() const;

	virtual UStrata* GetStrataController() const;

	virtual ~IOwnable() = default;
protected:
	UPROPERTY()
	UCountry* CountryController;

	UPROPERTY()
	UCountry* CountryOwner;

	UPROPERTY()
	UStrata* StrataOwner;
	
	UPROPERTY()
	UStrata* StrataController;
};


