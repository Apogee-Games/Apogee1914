#pragma once
#include "StorageGoodWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "StorageGoodsListWidget.generated.h"
UCLASS()
class UStorageGoodsListWidget: public UUserWidget, public IStorageObserver
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UGridPanel* ListGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStorageGoodWidget> StorageGoodWidgetClass;

	virtual void GoodIsUpdated(EStorageType StorageType, const FName& GoodName, int NewAmount) override;
	
private:
	UPROPERTY()
	TMap<FName, UStorageGoodWidget*> GoodsWidgets;

	int Count = 0;
};
