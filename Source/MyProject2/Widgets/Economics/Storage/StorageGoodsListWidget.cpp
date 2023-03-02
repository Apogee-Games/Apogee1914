#include "StorageGoodsListWidget.h"

void UStorageGoodsListWidget::GoodIsUpdated(EStorageType StorageType, UGood* Good)
{
	GoodsListView->AddItem(Good);
}
