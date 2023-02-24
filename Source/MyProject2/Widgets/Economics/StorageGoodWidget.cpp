#include "StorageGoodWidget.h"

void UStorageGoodWidget::Init(const FName& GoodName)
{
	GoodNameTextBlock->SetText(FText::FromName(GoodName));

	TypeTextBlockMapping.Add(EStorageType::Country, CountryStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::LowerStrata, LowerStrataStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::MiddleStrata, MiddleStrataStorageCountTextBlock);
	TypeTextBlockMapping.Add(EStorageType::UpperStrata, UpperStrataStorageCountTextBlock);

	for (const auto& [Type, TextBlock]: TypeTextBlockMapping)
	{
		TextBlock->SetText(FText::FromString("0"));
	}
}

void UStorageGoodWidget::GoodIsUpdated(EStorageType StorageType, int NewAmount)
{
	TypeTextBlockMapping[StorageType]->SetText(FText::FromString(FString::FromInt(NewAmount)));
}
