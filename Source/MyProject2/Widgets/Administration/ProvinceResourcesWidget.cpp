#include "ProvinceResourcesWidget.h"

void UProvinceResourcesWidget::SetResource(UObject* ProvidedResource)
{
	Resource = Cast<UProvinceResource>(ProvidedResource);
}

void UProvinceResourcesWidget::RefreshData()
{
	ResourceNameTextBlock->SetText(FText::FromName(Resource->GetResourceName()));
	UsedAmountTextBlock->SetText(FText::FromString(FString::FromInt(Resource->GetUsedAmount())));
	TotalAmountTextBlock->SetText(FText::FromString(FString::FromInt(Resource->GetTotalAmount())));
}
