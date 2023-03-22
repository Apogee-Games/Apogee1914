#include "Administration/Instances/Country.h"

#include "People/Managers/PeopleManager.h"
#include "Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	for (const auto FractionDescription: CountryDescription->Fractions)
	{
		Fractions.Add(FractionDescription.FractionTag, FractionDescription);
	}
	
	Tag = CountryDescription->Tag;
	
	SetRulingFraction(CountryDescription->RulingFractionTag);
	
	InitStrata();

	Storage = NewObject<UStorage>();
	Market = NewObject<UMarket>();
}

const FColor& UCountry::GetColor() const
{
	return Fractions[RulingFractionTag].CountryColor;
}

const FName& UCountry::GetName() const
{
	return Fractions[RulingFractionTag].CountryName;
}

const FName& UCountry::GetTag() const
{
	return Tag;
}

UTexture2D* UCountry::GetFlag()
{
	if (!Flag) LoadFlag();
	return Flag;
}

UStorage* UCountry::GetStorage() const
{
	return Storage;
}

void UCountry::SetRulingFraction(const FName& ProvidedRulingFractionTag)
{
	RulingFractionTag = ProvidedRulingFractionTag;
	UPeopleManager* PeopleManager = GetWorld()->GetGameInstance()->GetSubsystem<UPeopleManager>();
	Ruler = PeopleManager->GetPerson(Fractions[RulingFractionTag].RulerId);
	LoadFlag();
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
	return (CanCreateDefencivePactList & GetRelation(Country));
}

bool UCountry::CanCreateAllianceWith(UCountry* Country)
{
	return (CanCreateAllianceList & GetRelation(Country));
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

bool UCountry::IsCountryInWar() const
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

void UCountry::InitStrata()
{
	LowerStrata = NewObject<UStrata>();
	LowerStrata->Init("LOW");
	MiddleStrata = NewObject<UStrata>();
	MiddleStrata->Init("MIDDLE");
	UpperStrata = NewObject<UStrata>();
	UpperStrata->Init("UPPER");
	// TODO: Add proper initialization 
}

void UCountry::LoadFlag() 
{
	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag.ToString() + "/" + RulingFractionTag.ToString());
}
