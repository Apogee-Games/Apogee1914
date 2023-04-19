
#include "Widgets/Music/MusicControllerWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Widgets/Music/SongsGroupWidget.h"

void UMusicControllerWidget::Init(const TArray<USongsGroup*>& SongsGroups)
{
	PlayMusicButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnPlayMusicButton);
	ViewMusicListButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnViewMusicListButtonClick);
	PausePlaying();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMusicControllerWidget::UpdateProgress,1, true);
    
	for (const auto& Group: SongsGroups)
	{
		USongsGroupWidget* SongsGroupWidget = CreateWidget<USongsGroupWidget>(GetOwningPlayer(), SongsGroupWidgetClass);
		SongsGroupWidget->Init(Group, this);
		SongsGroupsScrollBox->AddChild(SongsGroupWidget);
	}
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
	ResumePlaying();
	
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
		if(IsPaused) ResumePlaying();
		else PausePlaying();
		GetOwningPlayerPawn<AHumanPlayerPawn>()->SetIsAudioPaused(IsPaused);
	}
}

void UMusicControllerWidget::UpdateProgress()
{
	if (SelectedSong && !IsPaused) {
		CurrentProgress++;
		const int Minutes = CurrentProgress/60;
		const int Seconds = CurrentProgress % 60;
		FString MinutesStr = Minutes < 10 ? "0" + FString::FromInt(Minutes) : FString::FromInt(Minutes);
		FString SecondsStr = Seconds < 10 ? "0" + FString::FromInt(Seconds) : FString::FromInt(Seconds);
		SongPlaybackProgressTextBlock->SetText(FText::FromString(MinutesStr + ":" + SecondsStr));
	}
}

void UMusicControllerWidget::ResumePlaying()
{
	IsPaused = false;
	PlayMusicButton->SetStyle(PauseStyle);
}

void UMusicControllerWidget::PausePlaying()
{
	IsPaused = true;
	PlayMusicButton->SetStyle(PlayStyle);
}
