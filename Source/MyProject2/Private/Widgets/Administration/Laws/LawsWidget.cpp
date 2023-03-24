
#include "Widgets/Administration/Laws/LawsWidget.h"

#include "Administration/Descriptions/LawDescription.h"
#include "Administration/Managers/LawManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void ULawsWidget::Init()
{
	LawDescriptionWidget->Init();
	
	const TArray<FLawDescription*>& CommonLaws = GetGameInstance()->GetSubsystem<ULawManager>()->GetCommonLaws();
	for (const auto& LawDescription: CommonLaws)
	{
		AddLaw(LawDescription);
	}

	FName Tag = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountryTag();
	const TArray<FLawDescription*>& CountrySpecific = GetGameInstance()->GetSubsystem<ULawManager>()->GetCountrySpecificLaw(Tag);
	for (const auto& LawDescription: CountrySpecific)
	{
		AddLaw(LawDescription);
	}
}

void ULawsWidget::AddLaw(FLawDescription* LawDescription)
{
	if (!Groups.Contains(LawDescription->Group))
	{
		int32 Index = GroupsWidgetSwitcher->GetNumWidgets();
			
		ULawsGroupButtonWidget* LawsGroupButtonWidget = CreateWidget<ULawsGroupButtonWidget>(GetOwningPlayer(), LawsGroupButtonWidgetClass);
		LawsGroupButtonWidget->Init(LawDescription->Group, GroupsWidgetSwitcher, Index);
		GroupsButtonsScrollBox->AddChild(LawsGroupButtonWidget);

		ULawsGroupWidget* LawsGroupWidget = CreateWidget<ULawsGroupWidget>(GetOwningPlayer(), LawsGroupWidgetClass);
		LawsGroupWidget->Init(LawDescriptionWidget);
		Groups.Add(LawDescription->Group, LawsGroupWidget);
		Indexes.Add(LawsGroupWidget, Index);
		GroupsWidgetSwitcher->AddChild(LawsGroupWidget);
	}
		
	Groups[LawDescription->Group]->AddLaw(LawDescription);
}
