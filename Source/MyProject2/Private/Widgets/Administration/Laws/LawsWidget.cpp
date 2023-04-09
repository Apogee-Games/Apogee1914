
#include "Widgets/Administration/Laws/LawsWidget.h"
#include "Administration/Managers/LawsManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void ULawsWidget::Init()
{
	LawDescriptionWidget->Init();

	ULawsManager* LawsManager = GetGameInstance()->GetSubsystem<ULawsManager>();
	
	for (const auto& LawsGroup: LawsManager->GetCommonLaws())
	{
		AddLawsGroup(LawsGroup);
	}
	
	UCountryDescription* CountryDescription = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetId();
	for (const auto& LawsGroup: LawsManager->GetCountrySpecificLaw(CountryDescription))
	{
		AddLawsGroup(LawsGroup);
	}
}

void ULawsWidget::AddLawsGroup(ULawsGroup* LawsGroup)
{
	ULawsGroupWidget* LawsGroupWidget = CreateWidget<ULawsGroupWidget>(GetOwningPlayer(), LawsGroupWidgetClass);
	LawsGroupWidget->Init(LawsGroup, LawDescriptionWidget);
	GroupsWidgetSwitcher->AddChild(LawsGroupWidget);

	ULawsGroupButtonWidget* LawsGroupButtonWidget = CreateWidget<ULawsGroupButtonWidget>(GetOwningPlayer(), LawsGroupButtonWidgetClass);
	LawsGroupButtonWidget->Init(LawsGroup, GroupsWidgetSwitcher, GroupsCount);
	GroupsButtonsScrollBox->AddChild(LawsGroupButtonWidget);

	++GroupsCount;
}