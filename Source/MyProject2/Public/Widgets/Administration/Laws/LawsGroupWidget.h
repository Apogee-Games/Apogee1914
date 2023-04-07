#pragma once
#include "LawButtonWidget.h"
#include "LawDescriptionWidget.h"
#include "LawsSubgroupWidget.h"
#include "Administration/Descriptions/Law/LawsGroup.h"
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
	
	void Init(ULawsGroup* LawsGroup, ULawDescriptionWidget* ProvidedLawDescriptionWidget);
private:
	UPROPERTY()
	ULawDescriptionWidget* LawDescriptionWidget;
	
	UPROPERTY()
	TMap<FName, ULawsSubgroupWidget*> Subgroups;

	void AddLawsSubgroup(ULawsSubgroup* LawsSubgroup);
};
