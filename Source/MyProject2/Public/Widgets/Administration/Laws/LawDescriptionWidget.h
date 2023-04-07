#pragma once
#include "LawConditionWidget.h"
#include "LawOutcomeWidget.h"
#include "Administration/Descriptions/Law/LawDescription.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/MultiLineEditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "LawDescriptionWidget.generated.h"

UCLASS()
class ULawDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LawNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UMultiLineEditableText* LawDescriptionTextBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* ConditionsScrollBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* OutcomesScrollBox;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* PassLawButton;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULawConditionWidget> LawConditionWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULawOutcomeWidget> LawOutcomeWidgetClass; 

	void Init();
		
	void SetLaw(ULawDescription* ProvidedLawDescription);

	void RefreshData();
private:
	UPROPERTY()
	ULawDescription* LawDescription;

	UFUNCTION()
	void OnPassLawButtonClick();
};
