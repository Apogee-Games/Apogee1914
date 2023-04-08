
#include "People/Instances/Person.h"

#include "InGameTime.h"

void UPerson::Init(UPersonDescription* Description)
{
	DateOfBirth = Description->DataOfBirth;
	Name = Description->Name;
	Professions = Description->Professions;
	Image = Description->Image;
}

int32 UPerson::GetAge() const
{
	return (GetWorld()->GetGameInstance()->GetSubsystem<UInGameTime>()->GetTime() - DateOfBirth).GetDays() / 365;
}

const FText& UPerson::GetPersonName() const
{
	return Name;
}

const TArray<UProfessionDescription*>& UPerson::GetProfessions() const
{
	return Professions;
}

UTexture2D* UPerson::GetImage() const
{
	return Image;
}
