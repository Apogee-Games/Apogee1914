#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Diplomacy/Instances/War.h"
#include "OurWarsListItemWidget.generated.h"

UCLASS()
class UOurWarsListItemWidget: public  UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* AttackerFlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* DefenderFlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* WarNameTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetWar(UObject* ProvidedWar);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UWar* War;

	UFUNCTION()
	void OnButtonClick();
};
