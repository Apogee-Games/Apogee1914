
#include "Widgets/Military/Creation/UnitTypeDescriptionWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"
#include "Widgets/Military/Carriers/GoodRequirementCarrier.h"


void UUnitTypeDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitTypeDescriptionWidget::OnButtonClick);
}

void UUnitTypeDescriptionWidget::SetUnitDescription(UObject* ProvidedUnitDescription)
{
	UnitDescription = Cast<UUnitDescription>(ProvidedUnitDescription);
	for (const auto& [Good, GoodRequirement]: UnitDescription->EquipmentRequirements)
	{
		if (AddedGoodRequirement.Contains(Good)) continue;
		UGoodRequirementCarrier* Carrier = NewObject<UGoodRequirementCarrier>();
		Carrier->Init(UnitDescription, Good);
		EquipmentRequirementsListView->AddItem(Carrier);
	}
}

void UUnitTypeDescriptionWidget::RefreshData()
{
	UnitNameTextBlock->SetText(FText::FromName(UnitDescription->UnitName));
	MilitaryBranchTextBlock->SetText(UnitDescription->MilitaryBranch->Name);
	ManpowerRequirementsTextBlock->SetText(FText::FromString(FString::FromInt(UnitDescription->ManpowerRequirements)));
}

void UUnitTypeDescriptionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectUnitDescription(UnitDescription);
}
