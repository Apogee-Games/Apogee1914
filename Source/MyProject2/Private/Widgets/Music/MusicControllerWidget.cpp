
#include "Widgets/Music/MusicControllerWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Widgets/Music/SongsGroupWidget.h"

void UMusicControllerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayMusicButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnPlayMusicButton);
	ViewMusicListButton->OnClicked.AddDynamic(this, &UMusicControllerWidget::OnViewMusicListButtonClick);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMusicControllerWidget::UpdateProgress,1, true);
}

void UMusicControllerWidget::AddSong(FSongDescription* SongDescription)
{
	if (!Groups.Contains(SongDescription->Group))
	{
		USongsGroupWidget* SongsGroupWidget = CreateWidget<USongsGroupWidget>(GetOwningPlayer(), SongsGroupWidgetClass);
		SongsGroupWidget->Init(SongDescription->Group, this);
		Groups.Add(SongDescription->Group, SongsGroupWidget);
		SongsGroupsScrollBox->AddChild(SongsGroupWidget);
	}
	Groups[SongDescription->Group]->AddSong(SongDescription);
}

void UMusicControllerWidget::Select(USongDescriptionWidget* SongDescriptionWidget)
{
	if (SelectedSong)
	{
		SelectedSong->UnSelect();
	}
	
	SelectedSong = SongDescriptionWidget;

	SelectedSong->Select();

	CurrentSongNameTextBlock->SetText(SelectedSong->GetSongDescription()->SongName);

	Song = LoadObject<USoundBase>(this, *SelectedSong->GetSongDescription()->Path);
	
	CurrentProgress = 0;
	IsPaused = false;
	
	GetOwningPlayerPawn<AHumanPlayerPawn>()->Play(Song);
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
