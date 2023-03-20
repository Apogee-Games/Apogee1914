#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "WarParticipantWidget.generated.h"

UCLASS()
class UWarParticipantWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* FlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* NameTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetCountry(UObject* ProvidedCountry);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UCountry* Country;
};
