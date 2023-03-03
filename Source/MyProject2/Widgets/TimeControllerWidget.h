#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TimeControllerWidget.generated.h"

UCLASS()
class MYPROJECT2_API UTimeControllerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SpeedUpButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SlowDownButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* PauseButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* TimeTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* SpeedProgressBar;

	virtual void NativeConstruct() override;
	
	void SetTime(const FString& Time);
private:
	UFUNCTION()
	void SpeedUpButtonOnClick();

	UFUNCTION()
	void SlowDownButtonOnClick();

	UFUNCTION()
	void PauseButtonOnClick();
};
