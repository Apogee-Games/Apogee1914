

#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"

void UStorageGoodsListWidget::GoodIsUpdated(EStorageType StorageType, UStoredGood* Good)
{
	GoodsListView->AddItem(Good);
}
