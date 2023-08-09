
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

	Unit->SetCountryOwner(Province->GetCountryController());
	Unit->SetCountryController(Province->GetCountryController());

	Unit->Init(Description, Province);
	
	Units.Add(Unit);
	
	return Unit;
}

UUnit* UUnitsFactory::CreateUnit(UUnitDescription* Description, UProvince* Province, UCountryDescription* CountryDescription)
{
	// TODO: Add some logic for delay
	//TODO: Error checks ?
	UUnit* Unit = NewObject<UUnit>(this, Description->MilitaryBranch->UnitClass);

	UCountry* CountryOwner = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(CountryDescription);

	Unit->SetCountryOwner(CountryOwner);
	Unit->SetCountryController(CountryOwner);
	
	Unit->Init(Description, Province);
	
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
	
	UnitCollection->SetCountryOwner(CountryOwner);
	UnitCollection->SetCountryController(CountryOwner);

	UnitCollection->Init(MilitaryBranch);

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
	UUnitsCollectionGroup* UnitCollectionGroup = NewObject<UUnitsCollectionGroup>(this);
	
	UnitCollectionGroup->SetCountryOwner(CountryOwner);
	UnitCollectionGroup->SetCountryController(CountryOwner);

	UnitCollectionGroup->Init(MilitaryBranch);

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
	Unit->Dissolve();
	
	if (!IsClearing)
	{
		Units.Remove(Unit);
	}
	
	Unit->MarkAsGarbage();
}

void UUnitsFactory::RemoveUnitCollection(UUnitsCollection* UnitsCollection, bool IsClearing)
{
	UnitsCollection->Dissolve();

	if (!IsClearing)
	{
		UnitsCollections.Remove(UnitsCollection);
	}

	UnitsCollection->MarkAsGarbage();
}

void UUnitsFactory::RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup, bool IsClearing)
{
	UnitsCollectionGroup->Dissolve();

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

const TArray<UUnit*>& UUnitsFactory::GetUnits() const
{
	return Units;
}

ELoadStage UUnitsFactory::GetLoadStage()
{
	return ELoadStage::UnitsFactory;
}

TArray<UUnit*> UUnitsFactory::GetCountryControlledUnits(UCountry* Country)
{
	TArray<UUnit*> FoundUnits;
	for (UUnit* Unit: Units)
	{
		if (Unit->GetCountryController() == Country)
		{
			Units.Add(Unit);
		}
	}
	return FoundUnits;
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
