
#include "Widgets/Military/Map/UnitInformationWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UUnitInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitInformationWidget::OnClicked);
}

void UUnitInformationWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UUnitsListCarrier>(ProvidedCarrier);
}

void UUnitInformationWidget::RefreshData()
{
	if (const UUnit* Unit = Carrier->GetFirst())
	{
		CountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->Num())));
		FlagImage->SetBrushResourceObject(Unit->GetCountryController()->GetFlag());
	}
}

void UUnitInformationWidget::OnClicked()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(Carrier->GetUnits());
}

