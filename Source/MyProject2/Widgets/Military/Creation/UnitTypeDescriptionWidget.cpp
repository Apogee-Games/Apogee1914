#include "UnitTypeDescriptionWidget.h"

#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Widgets/Military/Carriers/GoodRequirementCarrier.h"
#include "MyProject2/Widgets/Military/Carriers/UnitDescriptionCarrier.h"


void UUnitTypeDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitTypeDescriptionWidget::OnButtonClick);
}

void UUnitTypeDescriptionWidget::SetUnitDescription(UObject* ProvidedUnitDescription)
{
	UnitDescription = Cast<UUnitDescriptionCarrier>(ProvidedUnitDescription)->GetUnitDescription();
	for (const auto& [GoodName, GoodRequirement]: UnitDescription->EquipmentRequirements)
	{
		if (AddedGoodRequirement.Contains(GoodName)) continue;
		UGoodRequirementCarrier* Carrier = NewObject<UGoodRequirementCarrier>();
		Carrier->Init(UnitDescription, GoodName);
		EquipmentRequirementsListView->AddItem(Carrier);
	}
}

void UUnitTypeDescriptionWidget::RefreshData()
{
	UnitNameTextBlock->SetText(FText::FromName(UnitDescription->UnitName));
	MilitaryBranchTextBlock->SetText(FText::FromName(UnitDescription->MilitaryBranch));
	ManpowerRequirementsTextBlock->SetText(FText::FromString(FString::FromInt(UnitDescription->ManpowerRequirements)));
}

void UUnitTypeDescriptionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectUnitDescription(UnitDescription);
}
