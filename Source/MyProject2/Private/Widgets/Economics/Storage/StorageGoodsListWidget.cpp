

#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UStorageGoodsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCounty = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	for (UStorage* Storage: OwnerCounty->GetStorages())
	{
		Storage->OnStorageGoodUpdated.AddUObject(this, &ThisClass::GoodIsUpdated);
	}
}

void UStorageGoodsListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	for (UStorage* Storage: OwnerCounty->GetStorages())
	{
		Storage->OnStorageGoodUpdated.RemoveAll(this);
	}
}

void UStorageGoodsListWidget::GoodIsUpdated(EStorageType StorageType, UStoredGood* Good)
{
	GoodsListView->AddItem(Good);
}
