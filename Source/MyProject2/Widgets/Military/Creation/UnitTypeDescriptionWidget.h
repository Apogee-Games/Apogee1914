#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitTypeDescriptionWidget.generated.h"

UCLASS()
class UUnitTypeDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* MilitaryBranchTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ManpowerRequirementsTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* EquipmentRequirementsListView;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetUnitDescription(UObject* ProvidedUnitDescription);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	TSet<FName> AddedGoodRequirement;
	
	const FUnitDescription* UnitDescription;

	UFUNCTION()
	void OnButtonClick();
};
