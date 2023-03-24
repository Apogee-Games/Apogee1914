#include "Widgets/Administration/Laws/LawOutcomeWidget.h"

void ULawOutcomeWidget::Init(const FOutcome& Outcome)
{
	OutcomeDescriptionMultiLineEditableText->SetText(Outcome.Description);
}
