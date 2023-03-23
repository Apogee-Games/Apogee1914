#include "Widgets/Administration/Country/ParliamentWidget.h"

void UParliamentWidget::SetParliament(UParliament* ProvidedParliament)
{
	Parliament = ProvidedParliament;
	RefreshData();
}

void UParliamentWidget::RefreshData()
{
	ParliamentNameTextBlock->SetText(Parliament->GetName());
	for (const auto& [IdeologyTag, Fraction]: Parliament->GetFractionsMap())
	{
		FractionsListView->AddItem(Fraction);
	}
}
