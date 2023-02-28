#include "UnitsFactory.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Military/Instances/Units/Division.h"

FUnit* UUnitsFactory::Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	UUnitsRenderer* Renderer = GetWorld()->GetSubsystem<UUnitsRenderer>();
	return Create(Description, Province, CountryOwnerTag, Renderer);
}

FUnit* UUnitsFactory::Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag, UUnitsRenderer* Renderer)
{
	// TODO: Add some logic for delay
	UCountry* CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);
	FUnit* Unit = new FDivision(Description, Province, CountryOwner, Renderer); // TODO: Add other types
	NotifyUnitCreation(Unit);
	return Unit;
}

void UUnitsFactory::Remove(FUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
}