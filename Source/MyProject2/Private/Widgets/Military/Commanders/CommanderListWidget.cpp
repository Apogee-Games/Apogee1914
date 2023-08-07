#include "Widgets/Military/Commanders/CommanderListWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "People/Managers/PeopleManager.h"

void UCommanderListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CommandersListView->ClearListItems();
	
	UCountryDescription* CountryDescription = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetId();
	const TArray<UPerson*> People = GetGameInstance()->GetSubsystem<UPeopleManager>()->GetPeopleByProfession(CommanderProfession, CountryDescription);
	for (const auto& Person: People)
	{
		CommandersListView->AddItem(Person);
	}
}
