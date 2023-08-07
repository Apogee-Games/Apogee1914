#pragma once
#include "StorageGoodWidget.h"
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "StorageGoodsListWidget.generated.h"

UCLASS()
class UStorageGoodsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* GoodsListView;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UCountry* OwnerCounty;
	
	UFUNCTION()
	void GoodIsUpdated(EStorageType StorageType, UStoredGood* Good);
};
