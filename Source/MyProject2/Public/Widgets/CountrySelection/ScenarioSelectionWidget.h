#pragma once
#include "Scenario.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "ScenarioSelectionWidget.generated.h"

UCLASS()
class UScenarioSelectionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* ScenariosListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ActiveScenarioNameTextBlock;
	
	virtual void NativeConstruct() override;

	void SetScenario(UScenario* Scenario);
};
