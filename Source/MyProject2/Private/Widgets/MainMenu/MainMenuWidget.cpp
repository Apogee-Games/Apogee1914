#include "Widgets/MainMenu/MainMenuWidget.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SinglePlayerButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSinglePlayerButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClick);
}

void UMainMenuWidget::OnSinglePlayerButtonClick()
{
	UGameplayStatics::OpenLevel(this, TEXT("CountrySelection"));
}

void UMainMenuWidget::OnExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);;
}

void UMainMenuWidget::OnLoadStage(ELoadStage LoadStage)
{
	LoadingScreenProgressBar->SetPercent(1.0f * static_cast<int32>(LoadStage) / static_cast<int32>(ELoadStage::Finished));

	if (LoadStage == ELoadStage::Finished)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		return;
	}

	bool WasUpdated = false;
	
	if (UTexture2D** Image = LoadingScreenImages.Find(LoadStage))
	{
		LoadingScreenImage->SetBrushResourceObject(*Image);
		WasUpdated = true;
	}

	if (FText* Text = LoadingScreenInformation.Find(LoadStage))
	{
		LoadingInformationTextBlock->SetText(*Text);
		WasUpdated = true;
	}
}
