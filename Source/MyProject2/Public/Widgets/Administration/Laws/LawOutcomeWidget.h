#pragma once
#include "Actions/Description/Outcome.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableText.h"
#include "LawOutcomeWidget.generated.h"

UCLASS()
class ULawOutcomeWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UMultiLineEditableText* OutcomeDescriptionMultiLineEditableText;

	void Init(const FOutcome& Outcome);
};
