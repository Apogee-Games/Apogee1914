#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "UnitCollectionWidget.generated.h"

UCLASS()
class UUnitCollectionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CollectionSizeTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CommanderButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CommanderNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CommanderImage;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetUnitCollection(UObject* ProvidedUnitsCollection);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

private:
	UPROPERTY()
	UUnitsCollection* UnitsCollection;

	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnCommanderButtonClick();
};
