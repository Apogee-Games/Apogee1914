#include "Widgets/Administration/Laws/LawDescriptionWidget.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void ULawDescriptionWidget::Init()
{
	PassLawButton->OnClicked.AddDynamic(this, &ULawDescriptionWidget::OnPassLawButtonClick);
}

void ULawDescriptionWidget::SetLaw(FLawDescription* ProvidedLawDescription)
{
	LawDescription = ProvidedLawDescription;
	RefreshData();
}

void ULawDescriptionWidget::RefreshData()
{
	LawNameTextBlock->SetText(LawDescription->LawName);
	LawDescriptionTextBox->SetText(LawDescription->Description);
	
	FName CountryTag = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry()->GetTag();
	UConditionsCheckingSubsystem* Checker = GetWorld()->GetSubsystem<UConditionsCheckingSubsystem>();

	ConditionsScrollBox->ClearChildren();

	bool CanBePassed = true;
	
	for (auto& Condition: LawDescription->Conditions)
	{
		ULawConditionWidget* ConditionWidget = CreateWidget<ULawConditionWidget>(GetOwningPlayer(), LawConditionWidgetClass);

		const bool IsFulfilled = Checker->CheckCondition(Condition, CountryTag);

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
	FName CountryTag = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountryTag();
	GetWorld()->GetSubsystem<UOutcomesApplierSubsystem>()->ApplyOutcomes(LawDescription->Outcomes, CountryTag);
	SetLaw(LawDescription);
}
