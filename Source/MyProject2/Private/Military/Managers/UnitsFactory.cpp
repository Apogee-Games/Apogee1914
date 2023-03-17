
#include "Military/Managers/UnitsFactory.h"

#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UUnitsFactory::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

UUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	// TODO: Add some logic for delay
	//TODO: Error checks ?

	UUnit* Unit = NewObject<UUnit>(GetWorld(), MilitaryBranchUnitsTypes[Description->MilitaryBranch]);
	UCountry* CountryOwner = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);
	Unit->Init(Description, Province, CountryOwner);
	NotifyUnitCreation(Unit);
	return Unit;
}

UUnitsCollection* UUnitsFactory::CreateUnitCollection(EMilitaryBranch MilitaryBranch)
{
	UUnitsCollection* UnitCollection = NewObject<UUnitsCollection>();
	UnitCollection->Init(MilitaryBranch);
	NotifyUnitsCollectionCreation(UnitCollection);
	return UnitCollection;
}

UUnitsCollectionGroup* UUnitsFactory::CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch)
{
	UUnitsCollectionGroup* UnitCollectionGroup = NewObject<UUnitsCollectionGroup>();
	UnitCollectionGroup->Init(MilitaryBranch);
	NotifyUnitsCollectionGroupCreation(UnitCollectionGroup);
	return UnitCollectionGroup;
}

void UUnitsFactory::Remove(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
} 