#pragma once
#include "LawDescriptionWidget.h"
#include "Administration/Descriptions/LawDescription.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "LawButtonWidget.generated.h"

UCLASS()
class ULawButtonWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LawNameTextBlock;

	void Init(FLawDescription* ProvidedLawDescription, ULawDescriptionWidget* ProvidedLawsSubgroupWidget);
private:
	UPROPERTY()
	ULawDescriptionWidget* LawDescriptionWidget;
	
	FLawDescription* LawDescription;

	UFUNCTION()
	void OnButtonClick();
};
