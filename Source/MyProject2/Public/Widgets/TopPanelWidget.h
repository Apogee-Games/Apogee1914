#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TopPanelWidget.generated.h"

UCLASS()
class UTopPanelWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CountryFlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CountryFlagButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ManpowerTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BuildingsNumberTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* UnitCreationButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* StorageBrowsingButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SupplyBrowsingButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BuildingCreationButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* LawsBrowsingButton;

	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void OnUnitCreationButtonClick();

	UFUNCTION()
	void OnStorageBrowsingButtonClick();

	UFUNCTION()
	void OnSupplyBrowsingButton();

	UFUNCTION()
	void OnBuildingCreationButtonClick();

	UFUNCTION()
	void OnCountryFlagButtonClick();

	UFUNCTION()
	void OnLawsBrowsingButtonClick();
};
