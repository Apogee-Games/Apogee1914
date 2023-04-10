#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Economics/Instances/Buildings/FactoryBuilding.h"
#include "FactoryProductionWidget.generated.h"

UCLASS()
class UFactoryProductionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ProvinceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* FactoryNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ProductionGoodSelectionButton;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetFactory(UObject* ProvidedFactory);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UFactoryBuilding* Factory;

	UFUNCTION()
	void OnProductionGoodSelectionButtonClick();
};
