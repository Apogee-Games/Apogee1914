#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "People/Instances/Person.h"
#include "CommanderWidget.generated.h"

UCLASS()
class UCommanderWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CommanderImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* AgeTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* NameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button; 

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetCommander(UObject* ProvidedCommander);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

private:
	UPROPERTY()
	UPerson* Commander;

	UFUNCTION()
	void OnButtonClick();
};