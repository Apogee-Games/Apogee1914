#include "Widgets/Economics/Buildings/Production/ProducibleGoodsListWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Economics/Description/Buildings/FactoryDescription.h"
#include "Economics/Instances/Buildings/FactoryBuilding.h"

void UProducibleGoodsListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UFactoryBuilding* Factory = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetSelectedFactory();

	const FProducibleGoods& ProducibleGoods = Factory->GetDescription<UFactoryDescription>()->ProducibleGoods;
	AddGoods(ProducibleGoods.Goods);
	AddGoods(ProducibleGoods.GoodsSubgroups);
	AddGoods(ProducibleGoods.GoodsGroups);
}

void UProducibleGoodsListWidget::AddGood(UGoodDescription* Good)
{
	GoodsListView->AddItem(Good);
}

void UProducibleGoodsListWidget::AddGoods(const TArray<UGoodsGroup*>& GoodsGroups)
{
	for (const auto& Group: GoodsGroups)
	{
		AddGoods(Group->Subgroups);
	}
}

void UProducibleGoodsListWidget::AddGoods(const TArray<UGoodsSubgroup*>& GoodsSubgroups)
{
	for (const auto& Subgroup: GoodsSubgroups)
	{
		AddGoods(Subgroup->Goods);
	}
}

void UProducibleGoodsListWidget::AddGoods(const TArray<UGoodDescription*>& Goods)
{
	for (const auto& Good: Goods)
	{
		AddGood(Good);
	}
}
