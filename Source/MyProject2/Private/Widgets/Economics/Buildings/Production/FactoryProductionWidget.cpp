#include "Widgets/Economics/Buildings/Production/FactoryProductionWidget.h"
#include "Administration/Instances/Province.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/ProductionSelectionPawnState.h"

void UFactoryProductionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ProductionGoodSelectionButton->OnClicked.AddDynamic(this, &UFactoryProductionWidget::OnProductionGoodSelectionButtonClick);
}

void UFactoryProductionWidget::SetFactory(UObject* ProvidedFactory)
{
	Factory = Cast<UFactoryBuilding>(ProvidedFactory);
}

void UFactoryProductionWidget::RefreshData()
{
	ProvinceNameTextBlock->SetText(FText::FromName(Factory->GetProvince()->GetName()));
	FactoryNameTextBlock->SetText(Factory->GetName());
	if (Factory->GetGoodToProduce())
	{
		ProductionGoodSelectionButton->WidgetStyle.Normal.SetResourceObject(Factory->GetGoodToProduce()->Image);
		ProductionGoodSelectionButton->WidgetStyle.Hovered.SetResourceObject(Factory->GetGoodToProduce()->Image);
	}
}

void UFactoryProductionWidget::OnProductionGoodSelectionButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->SetProductionSelectionFactory(Factory);
	Pawn->SetPawnState(FProductionSelectionPawnState::GetInstance());
}
