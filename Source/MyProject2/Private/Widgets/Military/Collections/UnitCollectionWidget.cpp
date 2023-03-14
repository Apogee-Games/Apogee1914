#include "Widgets/Military/Collections/UnitCollectionWidget.h"

#include "Characters/HumanPlayerPawn.h"

void UUnitCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitCollectionWidget::OnButtonClick);
}

void UUnitCollectionWidget::SetUnitCollection(UObject* ProvidedUnitsCollection)
{
	UnitsCollection = Cast<UUnitsCollection>(ProvidedUnitsCollection);
}

void UUnitCollectionWidget::RefreshData()
{
	CollectionSizeTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollection->GetSize())));
}

void UUnitCollectionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollection);
}
