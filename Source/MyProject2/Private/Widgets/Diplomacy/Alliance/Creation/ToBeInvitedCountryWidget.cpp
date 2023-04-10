#include "Widgets/Diplomacy/Alliance/Creation/ToBeInvitedCountryWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void UToBeInvitedCountryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UToBeInvitedCountryWidget::OnButtonClick);
}

void UToBeInvitedCountryWidget::SetCountry(UObject* ProvidedCountry)
{
	Country = Cast<UCountry>(ProvidedCountry);
}

void UToBeInvitedCountryWidget::RefreshData()
{
	CountryFlag->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(Country->GetName());
}

void UToBeInvitedCountryWidget::OnButtonClick()
{
	GetOwningPlayer<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetAllianceCreationWidget()->RemoveToBeInvitedCountry(Country);
}
