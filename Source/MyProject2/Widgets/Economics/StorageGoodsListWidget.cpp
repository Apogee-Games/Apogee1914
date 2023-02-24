#include "StorageGoodsListWidget.h"

void UStorageGoodsListWidget::GoodIsUpdated(EStorageType StorageType, const FName& GoodName, int NewAmount)
{
	if (!GoodsWidgets.Contains(GoodName))
	{
		UStorageGoodWidget* Widget = CreateWidget<UStorageGoodWidget>(GetWorld(), StorageGoodWidgetClass);
		Widget->Init(GoodName);
		GoodsWidgets.Add(GoodName, Widget);
		ListGridPanel->AddChildToGrid(Widget, Count);
		++Count;
	}
	GoodsWidgets[GoodName]->GoodIsUpdated(StorageType, NewAmount);
}
