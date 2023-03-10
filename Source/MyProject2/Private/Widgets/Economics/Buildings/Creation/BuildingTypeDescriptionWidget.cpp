
#include "Widgets/Economics/Buildings/Creation/BuildingTypeDescriptionWidget.h"

#include "Characters/HumanPlayerPawn.h"
#include "Widgets/Economics/Buildings/Carriers/BuildingDescriptionCarrier.h"
#include "Widgets/Economics/Buildings/Carriers/GoodConsumptionCarrier.h"
#include "Widgets/Economics/Buildings/Carriers/GoodProductionCarrier.h"
#include "Widgets/Economics/Buildings/Carriers/ResourceConsumptionCarrier.h"

void UBuildingTypeDescriptionWidget::RefreshData()
{
	BuildingNameTextBlock->SetText(FText::FromName(BuildingDescription->BuildingName));
	MaxLaboursTextBlock->SetText(FText::FromString(FString::FromInt(BuildingDescription->MaxLabours)));

	for (const auto& [GoodName, Amount]: BuildingDescription->GoodConsumption)
	{
		UGoodConsumptionCarrier* Carrier = NewObject<UGoodConsumptionCarrier>();
		Carrier->Init(BuildingDescription, GoodName);
		GoodsConsumptionListView->AddItem(Carrier);	
	}

	for (const auto& [ResourceName, Amount]: BuildingDescription->ResourceConsumption)
	{
		UResourceConsumptionCarrier* Carrier = NewObject<UResourceConsumptionCarrier>();
		Carrier->Init(BuildingDescription, ResourceName);
		ResourcesConsumptionListView->AddItem(Carrier);	
	}

	for (const auto& [GoodName, Amount]: BuildingDescription->GoodOutput)
	{
		UGoodProductionCarrier* Carrier = NewObject<UGoodProductionCarrier>();
		Carrier->Init(BuildingDescription, GoodName);
		GoodsProductionListView->AddItem(Carrier);	
	}
	
}

void UBuildingTypeDescriptionWidget::OnClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectBuildingDescription(BuildingDescription);
}

void UBuildingTypeDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UBuildingTypeDescriptionWidget::OnClick);
}

void UBuildingTypeDescriptionWidget::SetCarrier(UObject* ProvidedCarrier)
{
	BuildingDescription = Cast<UBuildingDescriptionCarrier>(ProvidedCarrier)->GetBuildingDescription();
}
