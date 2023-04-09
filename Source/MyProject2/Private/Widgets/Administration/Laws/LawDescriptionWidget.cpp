#include "Widgets/Administration/Laws/LawDescriptionWidget.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void ULawDescriptionWidget::Init()
{
	PassLawButton->OnClicked.AddDynamic(this, &ULawDescriptionWidget::OnPassLawButtonClick);
}

void ULawDescriptionWidget::SetLaw(ULawDescription* ProvidedLawDescription)
{
	LawDescription = ProvidedLawDescription;
	RefreshData();
}

void ULawDescriptionWidget::RefreshData()
{
	LawNameTextBlock->SetText(LawDescription->Name);
	LawDescriptionTextBox->SetText(LawDescription->Description);
	
	UCountryDescription* CountryDescription = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetId();
	UConditionsCheckingSubsystem* Checker = GetGameInstance()->GetSubsystem<UConditionsCheckingSubsystem>();

	ConditionsScrollBox->ClearChildren();

	bool CanBePassed = true;
	
	for (auto& Condition: LawDescription->Conditions)
	{
		ULawConditionWidget* ConditionWidget = CreateWidget<ULawConditionWidget>(GetOwningPlayer(), LawConditionWidgetClass);

		const bool IsFulfilled = Checker->CheckCondition(Condition, CountryDescription);

		ConditionWidget->SetCondition(Condition, IsFulfilled);
		ConditionsScrollBox->AddChild(ConditionWidget);
		
		CanBePassed = CanBePassed & IsFulfilled;
	}

	OutcomesScrollBox->ClearChildren();

	for (const auto Outcome: LawDescription->Outcomes)
	{
		ULawOutcomeWidget* OutcomeWidget = CreateWidget<ULawOutcomeWidget>(GetOwningPlayer(), LawOutcomeWidgetClass);
		OutcomeWidget->Init(Outcome);
		OutcomesScrollBox->AddChild(OutcomeWidget);
	}

	PassLawButton->SetIsEnabled(CanBePassed);
}

void ULawDescriptionWidget::OnPassLawButtonClick()
{
	UCountryDescription* CountryDescription = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetId();
	GetGameInstance()->GetSubsystem<UOutcomesApplierSubsystem>()->ApplyOutcomes(LawDescription->Outcomes, CountryDescription);
	SetLaw(LawDescription);
}
