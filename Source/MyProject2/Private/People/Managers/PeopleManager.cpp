#include "People/Managers/PeopleManager.h"

void UPeopleManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	/*UDataTable* PeoplesDescriptions = FindObject<UDataTable>(nullptr, TEXT("/Game/Sources/people_desctiption"));
	for (const auto & [Name, Description]: PeoplesDescriptions->GetRowMap())
	{
		FPersonDescription* CastedDescription = reinterpret_cast<FPersonDescription*>(Description);
		for (const auto& ProfessionName: CastedDescription->Professions)
		{
			if (!ProfessionPeople.Contains(ProfessionName))
			{
				ProfessionPeople.Add(ProfessionName, {});
			}
			ProfessionPeople[ProfessionName].Add(CastedDescription);
		}
	}*/
}

const TArray<FPersonDescription*>& UPeopleManager::GetPeopleByProfession(const FName& Profession)
{
	return ProfessionPeople[Profession];
}
