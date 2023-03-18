#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class UMainMenuWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SinglePlayerButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* MultiplayerButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ExitButton;

	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnSinglePlayerButtonClick();

	UFUNCTION()
	void OnExitButtonClick();
};
