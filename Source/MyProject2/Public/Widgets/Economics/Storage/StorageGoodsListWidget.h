#pragma once
#include "StorageGoodWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Economics/Interfaces/Observers/StorageObserver.h"
#include "StorageGoodsListWidget.generated.h"
UCLASS()
class UStorageGoodsListWidget: public UUserWidget, public IStorageObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* GoodsListView;

	virtual void GoodIsUpdated(EStorageType StorageType, UStoredGood* Good) override;
};
