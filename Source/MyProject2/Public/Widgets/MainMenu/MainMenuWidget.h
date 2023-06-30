#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
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

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* LoadingScreenProgressBar;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LoadingInformationTextBlock;	
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* LoadingScreenImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ELoadStage, UTexture2D*> LoadingScreenImages;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ELoadStage, FText> LoadingScreenInformation;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnLoadStage(ELoadStage LoadStage);
private:
	UFUNCTION()
	void OnSinglePlayerButtonClick();

	UFUNCTION()
	void OnExitButtonClick();
};
