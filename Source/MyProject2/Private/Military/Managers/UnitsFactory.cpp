
#include "Military/Managers/UnitsFactory.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UUnitsFactory::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

UUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province)
{
	UUnit* Unit = NewObject<UUnit>(GetWorld(), MilitaryBranchUnitsTypes[Description->MilitaryBranch]);
	
	Unit->Init(Description, Province);

	Unit->SetCountryOwner(Province->GetCountryController());
	Unit->SetCountryController(Province->GetCountryController());

	NotifyUnitCreation(Unit);
	return Unit;
}

UUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	// TODO: Add some logic for delay
	//TODO: Error checks ?
	UUnit* Unit = NewObject<UUnit>(GetWorld(), MilitaryBranchUnitsTypes[Description->MilitaryBranch]);

	Unit->Init(Description, Province);
	
	UCountry* CountryOwner = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);

	Unit->SetCountryOwner(CountryOwner);
	Unit->SetCountryController(CountryOwner);
	
	NotifyUnitCreation(Unit);

	return Unit;
}

UUnitsCollection* UUnitsFactory::CreateUnitCollection(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner)
{
	UUnitsCollection* UnitCollection = NewObject<UUnitsCollection>();
	
	UnitCollection->Init(MilitaryBranch);

	UnitCollection->SetCountryOwner(CountryOwner);
	UnitCollection->SetCountryController(CountryOwner);

	NotifyUnitsCollectionCreation(UnitCollection);
	return UnitCollection;
}

UUnitsCollectionGroup* UUnitsFactory::CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner)
{
	UUnitsCollectionGroup* UnitCollectionGroup = NewObject<UUnitsCollectionGroup>();
	
	UnitCollectionGroup->Init(MilitaryBranch);

	UnitCollectionGroup->SetCountryOwner(CountryOwner);
	UnitCollectionGroup->SetCountryController(CountryOwner);
	
	NotifyUnitsCollectionGroupCreation(UnitCollectionGroup);
	return UnitCollectionGroup;
}

void UUnitsFactory::RemoveUnit(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
}

void UUnitsFactory::RemoveUnitCollection(UUnitsCollection* UnitsCollection)
{
	NotifyUnitsCollectionRemoval(UnitsCollection);
	delete UnitsCollection;
}

void UUnitsFactory::RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	NotifyUnitsCollectionGroupRemoval(UnitsCollectionGroup);
	delete UnitsCollectionGroup;
}