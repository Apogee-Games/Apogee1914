
#include "People/Instances/Person.h"

#include "InGameTime.h"

void UPerson::Init(const FName& ProvidedId, const FPersonDescription* Description)
{
	Id = ProvidedId;
	DateOfBirth = Description->Age;
	PersonName = Description->PersonName;
	Professions = Description->Professions;
	Image = LoadObject<UTexture2D>(nullptr, *Description->ImagePath.ToString());
}

const FName& UPerson::GetId() const
{
	return Id;
}

int32 UPerson::GetAge() const
{
	return (GetWorld()->GetSubsystem<UInGameTime>()->GetTime() - DateOfBirth).GetDays() / 365;
}

FName UPerson::GetPersonName() const
{
	return PersonName;
}

const TArray<FName>& UPerson::GetProfessions() const
{
	return Professions;
}

UTexture2D* UPerson::GetImage() const
{
	return Image;
}
