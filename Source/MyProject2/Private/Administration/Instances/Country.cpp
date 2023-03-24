#include "Administration/Instances/Country.h"

#include "Administration/Managers/IdeologyManager.h"
#include "People/Managers/PeopleManager.h"
#include "Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription, FParliamentDescription* FirstChamber, FParliamentDescription* SecondChamber)
{

	if (FirstChamber) {
		FirstChamberParliament = NewObject<UParliament>(this);
		FirstChamberParliament->Init(FirstChamber);
	}
	
	if (SecondChamber) {
		SecondChamberParliament = NewObject<UParliament>(this);
		SecondChamberParliament->Init(FirstChamber);
	}
	
	
	for (const auto IdeologyDescription: CountryDescription->Ideologies)
	{
		Ideologies.Add(IdeologyDescription.IdeologyTag, IdeologyDescription);
	}
	
	Tag = CountryDescription->Tag;
	
	SetIdeology(CountryDescription->IdeologyTag);
	
	InitStrata();

	Storage = NewObject<UStorage>();
	Market = NewObject<UMarket>();
}

const FColor& UCountry::GetColor() const
{
	return Ideologies[Ideology->GetTag()].CountryColor;
}

const FName& UCountry::GetName() const
{
	return Ideologies[Ideology->GetTag()].CountryName;
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

void UCountry::SetIdeology(const FName& ProvidedIdeologyTag)
{
	Ideology = GetWorld()->GetGameInstance()->GetSubsystem<UIdeologyManager>()->GetIdeology(ProvidedIdeologyTag);
	
	UPeopleManager* PeopleManager = GetWorld()->GetGameInstance()->GetSubsystem<UPeopleManager>();
	Ruler = PeopleManager->GetPerson(Ideologies[Ideology->GetTag()].RulerId);
	
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

bool UCountry::IsCountryInWarWith(UCountry* Country)
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

UIdeology* UCountry::GetIdeology() const
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
	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag.ToString() + "/" + Ideology->GetTag().ToString());
}
