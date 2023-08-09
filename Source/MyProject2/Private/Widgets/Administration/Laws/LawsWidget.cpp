
#include "Widgets/Administration/Laws/LawsWidget.h"

#include "MyGameInstance.h"
#include "Administration/Managers/LawsManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void ULawsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!bIsInitialized)
	{
		ULawsManager* LawsManager = GetGameInstance()->GetSubsystem<ULawsManager>(); // TODO: Do I need this way of adding it ?
		for (const auto& LawsGroup: LawsManager->GetCommonLaws())
		{
			AddLawsGroup(LawsGroup);
		}
	
		UCountryDescription* CountryDescription = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetId();
		for (const auto& LawsGroup: LawsManager->GetCountrySpecificLaw(CountryDescription))
		{
			AddLawsGroup(LawsGroup);
		}
		
		bIsInitialized = true;
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
