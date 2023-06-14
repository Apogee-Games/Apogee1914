#include "Administration/Instances/Country.h"

#include "People/Managers/PeopleManager.h"

void UCountry::Init(UCountryDescription* ProvidedCountryDescription)
{
	CountryDescription = ProvidedCountryDescription;
	if (ProvidedCountryDescription->HasFirstChamber || ProvidedCountryDescription->HasTwoChambers) {
		FirstChamberParliament = NewObject<UParliament>(this);
		FirstChamberParliament->Init(ProvidedCountryDescription->FirstChamber);
	}
	
	if (ProvidedCountryDescription->HasTwoChambers) {
		SecondChamberParliament = NewObject<UParliament>(this);
		SecondChamberParliament->Init(ProvidedCountryDescription->SecondChamber);
	}
	
	for (const auto& IdeologyDescription: ProvidedCountryDescription->Ideologies)
	{
		IdeologiesParameters.Add(IdeologyDescription.Ideology, IdeologyDescription);
	}
	
	Tag = ProvidedCountryDescription->Tag;
	
	SetIdeology(ProvidedCountryDescription->CurrentIdeology);
	
	InitStrata();

	Storage = NewObject<UStorage>(this);
	Market = NewObject<UMarket>(this);
}

UCountryDescription* UCountry::GetId() const
{
	return CountryDescription;
}

const FColor& UCountry::GetColor() const
{
	return IdeologiesParameters[Ideology].Color;
}

const FText& UCountry::GetName() const
{
	return IdeologiesParameters[Ideology].Name;
}

const FName& UCountry::GetTag() const
{
	return Tag;
}

UTexture2D* UCountry::GetFlag()
{
	return IdeologiesParameters[Ideology].Flag;
}

UStorage* UCountry::GetStorage() const
{
	return Storage;
}

void UCountry::SetIdeology(UIdeologyDescription* ProvidedIdeology)
{
	Ideology = ProvidedIdeology;
	UPeopleManager* PeopleManager = GetWorld()->GetGameInstance()->GetSubsystem<UPeopleManager>();
	if (PeopleManager) {
		UPersonDescription* PersonDescription = IdeologiesParameters[ProvidedIdeology].Ruler;
		if (PersonDescription)
		{
			Ruler = PeopleManager->GetPerson(PersonDescription);
		}
	}
}

UPerson* UCountry::GetRuler() const
{
	return Ruler;
}

TArray<UStorage*> UCountry::GetStorages() const
{
	return {Storage, LowerStrata->GetStorage(), MiddleStrata->GetStorage(), UpperStrata->GetStorage()};
}

void UCountry::SetAlliance(UAlliance* ProvidedAlliance)
{
	Alliance = ProvidedAlliance;
}

UAlliance* UCountry::GetAlliance() const
{
	return Alliance;
}

bool UCountry::IsInAlliance() const
{
	return Alliance != nullptr;
}

ERelationType UCountry::GetRelation(UCountry* Country)
{
	return Relations.Contains(Country) ? Relations[Country] : Neutral;
}

void UCountry::SetRelation(UCountry* Country, ERelationType Relation)
{
	if (Relation == Neutral)
	{
		Relations.Remove(Country);
	} else {
		Relations.Add(Country, Relation);
	}
}

bool UCountry::CanDeclareWarOn(UCountry* Country)
{
	return (CanDeclareWarList & GetRelation(Country));
}

bool UCountry::CanCreateNonAggressionPactWith(UCountry* Country)
{
	return (CanCreateNonAggressionPactList & GetRelation(Country));
}

bool UCountry::CanCreateDefencivePactWith(UCountry* Country)
{
	return (CanCreateDefencivePactList & GetRelation(Country)) && !bIsNonAligned;
}

bool UCountry::CanCreateAllianceWith(UCountry* Country)
{
	return (CanCreateAllianceList & GetRelation(Country))  && !bIsNonAligned;
}

bool UCountry::MustHelpInDefenciveWar(UCountry* Country)
{
	return (MustHelpInDefenciveWarList & GetRelation(Country));
}

bool UCountry::MustHelpInAggressiveWar(UCountry* Country)
{
	return (MustHelpInAggressiveWarList & GetRelation(Country));
}

bool UCountry::CanJoinCountryWar(UCountry* Country)
{
	return (CanJoinCountriesWarList & GetRelation(Country));
}

bool UCountry::HasNonAggressionPactWith(UCountry* Country)
{
	return Relations.Contains(Country) && Relations[Country] == NonAggressionPact;
}

bool UCountry::HasDefencivePactWith(UCountry* Country)
{
	return Relations.Contains(Country) && Relations[Country] == DefencivePact;
}

const TMap<UCountry*, ERelationType>& UCountry::GetRelations() const
{
	return Relations;
}

void UCountry::AddWar(UWar* War)
{
	Wars.Add(War);
}

void UCountry::RemoveWar(UWar* War)
{
	Wars.Remove(War);
}

const TArray<UWar*>& UCountry::GetWars() const
{
	return Wars;
}

bool UCountry::IsInWar() const
{
	return !Wars.IsEmpty();
}

bool UCountry::CanCountryJoinOneOfOurWars(UCountry* Country) const
{
	for (const auto& War: Wars)
	{
		if (!War->IsMember(Country)) //TODO: Add logic to check if country can join :)
		{
			return true;
		}
	}
	return false;
}

bool UCountry::IsInWarWith(UCountry* Country)
{
	return Relations.Contains(Country) && Relations[Country] == War;
}

UParliament* UCountry::GetFirstChamber() const
{
	return FirstChamberParliament;
}

UParliament* UCountry::GetSecondChamber() const
{
	return SecondChamberParliament;
}

UIdeologyDescription* UCountry::GetIdeology() const
{
	return Ideology;
}

void UCountry::SetIsNonAligned(bool IsNonAligned)
{
	bIsNonAligned = IsNonAligned;
	if (!bIsNonAligned && Alliance)
	{
		Alliance->RemoveMember(this);
	}
}

bool UCountry::IsNonAligned() const
{
	return bIsNonAligned;
}

void UCountry::AddProvince(UProvince* Province)
{
	Provinces.Add(Province);
}

void UCountry::RemoveProvince(UProvince* Province)
{
	Provinces.Remove(Province);
}

const TArray<UProvince*>& UCountry::GetProvinces() const
{
	return Provinces;
}

void UCountry::InitStrata()
{
	LowerStrata = NewObject<UStrata>(this);
	LowerStrata->Init("LOW");
	MiddleStrata = NewObject<UStrata>(this);
	MiddleStrata->Init("MIDDLE");
	UpperStrata = NewObject<UStrata>(this);
	UpperStrata->Init("UPPER");
	// TODO: Add proper initialization 
}