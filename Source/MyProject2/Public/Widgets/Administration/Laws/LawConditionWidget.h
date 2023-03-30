#pragma once
#include "Actions/Description/Condition.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableText.h"
#include "Components/TextBlock.h"
#include "LawConditionWidget.generated.h"

UCLASS()
class ULawConditionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UMultiLineEditableText* ConditionDescriptionMultiLineEditableText;

	UPROPERTY(EditDefaultsOnly)
	FColor FulfilledConditionColor = FColor(0, 255, 0);
	
	UPROPERTY(EditDefaultsOnly)
	FColor NotFulfilledConditionColor = FColor(255, 0, 0);
	
	void SetCondition(const FCondition& Condition, bool IsFulfilled);
};
