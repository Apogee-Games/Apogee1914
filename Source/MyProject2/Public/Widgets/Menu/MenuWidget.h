#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuWidget.generated.h"

UCLASS()
class UMenuWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SaveGameButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* LoadGameButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ExitGameButton;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnResumeButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnExitGameButtonClick();
};
