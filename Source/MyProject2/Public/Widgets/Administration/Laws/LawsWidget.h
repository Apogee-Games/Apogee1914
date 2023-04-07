#pragma once
#include "LawsGroupButtonWidget.h"
#include "LawsGroupWidget.h"
#include "Administration/Descriptions/Law/LawsGroup.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "LawsWidget.generated.h"

UCLASS()
class ULawsWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* GroupsButtonsScrollBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* GroupsWidgetSwitcher;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	ULawDescriptionWidget* LawDescriptionWidget;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULawsGroupButtonWidget> LawsGroupButtonWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULawsGroupWidget> LawsGroupWidgetClass;

	void Init();
private:
	int GroupsCount = 0;
	
	void AddLawsGroup(ULawsGroup* LawsGroup);
};
