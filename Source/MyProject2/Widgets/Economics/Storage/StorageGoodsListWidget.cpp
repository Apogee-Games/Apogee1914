#include "StorageGoodsListWidget.h"

void UStorageGoodsListWidget::GoodIsUpdated(EStorageType StorageType, UStoredGood* Good)
{
	GoodsListView->AddItem(Good);
}
