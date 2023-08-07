#include "Widgets/Music/MusicControllerWidget.h"
#include "MyGameInstance.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Widgets/Music/SongsGroupWidget.h"

void UMusicControllerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayMusicButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnPlayMusicButton);
	ViewMusicListButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnViewMusicListButtonClick);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMusicControllerWidget::UpdateProgress,1, true);

	for (const auto& Group: GetGameInstance<UMyGameInstance>()->ActiveScenario->SongsGroups)
	{
		USongsGroupWidget* SongsGroupWidget = CreateWidget<USongsGroupWidget>(GetOwningPlayer(), SongsGroupWidgetClass);
		SongsGroupWidget->Init(Group, this);
		SongsGroupsScrollBox->AddChild(SongsGroupWidget);
	}
}

void UMusicControllerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	PlayMusicButton->OnClicked.RemoveAll(this);
	ViewMusicListButton->OnClicked.RemoveAll(this);
}

void UMusicControllerWidget::Select(USongDescriptionWidget* SongDescriptionWidget)
{
	if (SelectedSong)
	{
		SelectedSong->UnSelect();
	}
	
	SelectedSong = SongDescriptionWidget;

	SelectedSong->Select();

	CurrentSongNameTextBlock->SetText(SelectedSong->GetSongDescription()->Name);
	
	CurrentProgress = 0;
	IsPaused = false;
	
	GetOwningPlayerPawn<AHumanPlayerPawn>()->Play(SelectedSong->GetSongDescription()->Song);
}

void UMusicControllerWidget::OnViewMusicListButtonClick()
{
	const bool IsHidden = MusicDescriptionWidgetSwitcher->GetActiveWidgetIndex() == 1;
	MusicDescriptionWidgetSwitcher->SetActiveWidgetIndex(!IsHidden);
}

void UMusicControllerWidget::OnPlayMusicButton()
{
	if (SelectedSong)
	{
		IsPaused = !IsPaused;
		GetOwningPlayerPawn<AHumanPlayerPawn>()->SetIsAudioPaused(IsPaused);
	}
}

void UMusicControllerWidget::UpdateProgress()
{
	if (SelectedSong && !IsPaused) {
		CurrentProgress++;
		SongPlaybackProgressTextBlock->SetText(FText::FromString(FString::FromInt(CurrentProgress)));
	}
}
