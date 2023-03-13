#include "Widgets/Military/Collections/UnitCollectionWidget.h"

void UUnitCollectionWidget::SetUnitCollection(UObject* ProvidedUnitsCollection)
{
	UnitsCollection = Cast<UUnitsCollection>(ProvidedUnitsCollection);
}

void UUnitCollectionWidget::RefreshData()
{
	CollectionSizeTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollection->GetSize())));
}
