#include "StorageGoodWidget.h"


void UStorageGoodWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TypeTextBlockMapping.Add(EStorageType::Country, CountryStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::LowerStrata, LowerStrataStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::MiddleStrata, MiddleStrataStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::UpperStrata, UpperStrataStorageCountTextBlock);

	for (const auto& [Type, TextBlock]: TypeTextBlockMapping)
	{
		TextBlock->SetText(FText::FromString("0"));
	}
}

void UStorageGoodWidget::SetGood(UObject* ProvidedGood)
{
	Good = Cast<UGood>(ProvidedGood);
}

void UStorageGoodWidget::RefreshData()
{
	GoodNameTextBlock->SetText(FText::FromName(Good->GetGoodName()));
	TypeTextBlockMapping[Good->GetStorage()->GetType()]->SetText(FText::FromString(FString::FromInt(Good->GetAmount())));
}
