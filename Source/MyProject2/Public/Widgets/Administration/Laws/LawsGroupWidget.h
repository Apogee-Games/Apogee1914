#pragma once
#include "LawButtonWidget.h"
#include "LawDescriptionWidget.h"
#include "LawsSubgroupWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "LawsGroupWidget.generated.h"

UCLASS()
class ULawsGroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* LawsSubgroupsScrollBox;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULawsSubgroupWidget> LawsSubgroupWidgetClass;
	
	void SelectLaw(FLawDescription* LawDescription);

	void AddLaw(FLawDescription* LawDescription);
	
	void Init(ULawDescriptionWidget* ProvidedLawDescriptionWidget);
private:
	UPROPERTY()
	ULawDescriptionWidget* LawDescriptionWidget;
	
	UPROPERTY()
	TMap<FName, ULawsSubgroupWidget*> Subgroups;
};
