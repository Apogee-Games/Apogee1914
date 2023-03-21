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
