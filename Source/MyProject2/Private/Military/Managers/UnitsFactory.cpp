
#include "Military/Managers/UnitsFactory.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"

void UUnitsFactory::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UUnit* UUnitsFactory::CreateUnit(UUnitDescription* Description, UProvince* Province)
{
	UUnit* Unit = NewObject<UUnit>(this, Description->MilitaryBranch->UnitClass);
	
	Unit->Init(Description, Province);

	Unit->SetCountryOwner(Province->GetCountryController());
	Unit->SetCountryController(Province->GetCountryController());

	NotifyUnitCreation(Unit);
	Units.Add(Unit);
	
	return Unit;
}

UUnit* UUnitsFactory::CreateUnit(UUnitDescription* Description, UProvince* Province, UCountryDescription* CountryDescription)
{
	// TODO: Add some logic for delay
	//TODO: Error checks ?
	UUnit* Unit = NewObject<UUnit>(this, Description->MilitaryBranch->UnitClass);

	Unit->Init(Description, Province);
	
	UCountry* CountryOwner = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(CountryDescription);

	Unit->SetCountryOwner(CountryOwner);
	Unit->SetCountryController(CountryOwner);
	
	NotifyUnitCreation(Unit);
	Units.Add(Unit);

	return Unit;
}

UUnitsCollection* UUnitsFactory::CreateUnitCollection(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner, const TArray<UUnit*>& UnitsToAdd)
{
	UUnitsCollection* UnitsCollection = CreateUnitCollection(MilitaryBranch, CountryOwner);
	for (const auto& Unit: UnitsToAdd)
	{
		UnitsCollection->Add(Unit);
	}
	UnitsCollections.Add(UnitsCollection);
	return UnitsCollection;
}

UUnitsCollection* UUnitsFactory::CreateUnitCollection(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner)
{
	UUnitsCollection* UnitCollection = NewObject<UUnitsCollection>(this); 
	
	UnitCollection->Init(MilitaryBranch);

	UnitCollection->SetCountryOwner(CountryOwner);
	UnitCollection->SetCountryController(CountryOwner);

	NotifyUnitsCollectionCreation(UnitCollection);
	UnitsCollections.Add(UnitCollection);
	return UnitCollection;
}

UUnitsCollectionGroup* UUnitsFactory::CreateUnitCollectionGroup(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner, const TArray<UUnitsCollection*>& UnitsCollectionsToAdd)
{
	UUnitsCollectionGroup* UnitsCollectionGroup = CreateUnitCollectionGroup(MilitaryBranch, CountryOwner);
	for (const auto& UnitsCollection: UnitsCollectionsToAdd)
	{
		UnitsCollectionGroup->Add(UnitsCollection);
	}
	UnitsCollectionGroups.Add(UnitsCollectionGroup);
	return UnitsCollectionGroup;
}

UUnitsCollectionGroup* UUnitsFactory::CreateUnitCollectionGroup(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner)
{
	UUnitsCollectionGroup* UnitCollectionGroup = NewObject<UUnitsCollectionGroup>();
	
	UnitCollectionGroup->Init(MilitaryBranch);

	UnitCollectionGroup->SetCountryOwner(CountryOwner);
	UnitCollectionGroup->SetCountryController(CountryOwner);
	
	NotifyUnitsCollectionGroupCreation(UnitCollectionGroup);
	UnitsCollectionGroups.Add(UnitCollectionGroup);
	return UnitCollectionGroup;
}

void UUnitsFactory::RemoveUnits(const TArray<UUnit*>& UnitsToRemove, bool IsClearing)
{
	for (const auto& Unit: UnitsToRemove)
	{
		RemoveUnit(Unit, IsClearing);
	}
}

void UUnitsFactory::RemoveUnit(UUnit* Unit, bool IsClearing)
{
	NotifyUnitRemoval(Unit);
	
	UUnitsCollection* Collection = Unit->GetUnitsCollection();
	if (Collection)
	{
		Collection->Remove(Unit);
	}

	Unit->GetPosition()->RemoveUnit(Unit);

	if (!IsClearing)
	{
		Units.Remove(Unit);
	}
	
	
	Unit->MarkAsGarbage();
}

void UUnitsFactory::RemoveUnitCollection(UUnitsCollection* UnitsCollection, bool IsClearing)
{
	NotifyUnitsCollectionRemoval(UnitsCollection);

	UUnitsCollectionGroup* CollectionGroup = UnitsCollection->GetUnitsCollectionGroup();
	if (CollectionGroup)
	{
		CollectionGroup->Remove(UnitsCollection);
	}

	UnitsCollection->ClearUnits();

	if (!IsClearing)
	{
		UnitsCollections.Remove(UnitsCollection);
	}

	
	UnitsCollection->MarkAsGarbage();
}

void UUnitsFactory::RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup, bool IsClearing)
{
	NotifyUnitsCollectionGroupRemoval(UnitsCollectionGroup);

	UnitsCollectionGroup->ClearCollections();

	if (!IsClearing)
	{
		UnitsCollectionGroups.Remove(UnitsCollectionGroup);

	}
	
	UnitsCollectionGroup->MarkAsGarbage();
}

const TArray<UMilitaryBranchDescription*>& UUnitsFactory::GetMilitaryBranches() const
{
	return MilitaryBranches;
}

const TArray<UUnitDescription*>& UUnitsFactory::GetUnitsDescriptions() const
{
	return UnitDescriptions;
}

void UUnitsFactory::Clear()
{
	for (const auto& Unit: Units)
	{
		RemoveUnit(Unit, true);
	}
	for (const auto& UnitsCollection: UnitsCollections)
	{
		RemoveUnitCollection(UnitsCollection, true);
	}
	for (const auto& UnitsCollectionGroup: UnitsCollectionGroups)
	{
		RemoveUnitCollectionGroup(UnitsCollectionGroup, true);
	}
	Units.Empty();
	UnitsCollections.Empty();
	UnitsCollectionGroups.Empty();
	UnitDescriptions.Empty();
	MilitaryBranches.Empty();
}

void UUnitsFactory::Init(UScenario* Scenario)
{
	UnitDescriptions = Scenario->UnitDescriptions;
	MilitaryBranches = Scenario->MilitaryBranches;
}
