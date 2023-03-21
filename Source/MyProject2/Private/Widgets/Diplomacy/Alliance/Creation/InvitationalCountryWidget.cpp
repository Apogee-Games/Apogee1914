#include "Widgets/Diplomacy/Alliance/Creation/InvitationalCountryWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void UInvitationalCountryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UInvitationalCountryWidget::OnButtonClick);
}

void UInvitationalCountryWidget::SetCountry(UObject* ProvidedCountry)
{
	Country = Cast<UCountry>(ProvidedCountry);
}

void UInvitationalCountryWidget::RefreshData()
{
	CountryFlag->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(FText::FromName(Country->GetName()));
}

void UInvitationalCountryWidget::OnButtonClick()
{
	GetOwningPlayer<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetAllianceCreationWidget()->AddToBeInvitedCountry(Country);
}
