#pragma once
#include "ProducibleGoodWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "Economics/Description/Goods/GoodsGroup.h"
#include "Economics/Description/Goods/GoodsSubgroup.h"
#include "ProducibleGoodsListWidget.generated.h"

UCLASS()
class UProducibleGoodsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* GoodsListView;

	virtual void NativeConstruct() override;
private:
	void AddGood(UGoodDescription* Good);

	void AddGoods(const TArray<UGoodsGroup*>& GoodsGroups);
	
	void AddGoods(const TArray<UGoodsSubgroup*>& GoodsSubgroup);
	
	void AddGoods(const TArray<UGoodDescription*>& Goods);
};
