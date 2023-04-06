#include "Widgets/Economics/Buildings/Production/ProducibleGoodWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/ProductionBrowsingPawnState.h"

void UProducibleGoodWidget::SetGood(UObject* ProvidedGood)
{
	Good = Cast<UCookedGoodDescription>(ProvidedGood);
}

void UProducibleGoodWidget::RefreshData()
{
	GoodImage->SetBrushResourceObject(Good->Image);
	GoodNameTextBlock->SetText(Good->NameText);
}

void UProducibleGoodWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UProducibleGoodWidget::OnButtonClick);
}

void UProducibleGoodWidget::OnButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->GetSelectedFactory()->SetGoodToProduce(Good);
	Pawn->SetPawnState(FProductionBrowsingPawnState::GetInstance());
}
