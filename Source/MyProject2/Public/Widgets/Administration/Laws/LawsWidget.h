#pragma once
#include "LawsGroupButtonWidget.h"
#include "LawsGroupWidget.h"
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
	UPROPERTY()
	TMap<FName, ULawsGroupWidget*> Groups;

	UPROPERTY()
	TMap<ULawsGroupWidget*, int32> Indexes;

	void AddLaw(FLawDescription* LawDescription);
};
