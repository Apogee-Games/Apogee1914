#include "Widgets/Military/Commanders/CommanderListWidget.h"

void UCommanderListWidget::AddCommander(UPerson* Commander)
{
	CommandersListView->AddItem(Commander);
}
