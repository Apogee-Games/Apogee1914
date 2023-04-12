#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Music/Description/SongDescription.h"
#include "Music/Description/SongsGroup.h"
#include "MusicControllerWidget.generated.h"

class USongsGroupWidget;
class USongDescriptionWidget;

UCLASS()
class UMusicControllerWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* PlayMusicButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ViewMusicListButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CurrentSongNameTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SongPlaybackProgressTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* MusicDescriptionWidgetSwitcher;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* SongsGroupsScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USongsGroupWidget> SongsGroupWidgetClass; 
	
	void Init(const TArray<USongsGroup*>& SongsGroups);
	
	void Select(USongDescriptionWidget* SongDescriptionWidget);
private:
	FTimerHandle TimerHandle;

	FButtonStyle PlayStyle;
	FButtonStyle PauseStyle;

	void ResumePlaying();

	void PausePlaying();
	
	bool IsPaused = true;
	
	int32 CurrentProgress = 0;
	
	UPROPERTY()
	USoundBase* Song;
	
	UPROPERTY()
	USongDescriptionWidget* SelectedSong;

	UFUNCTION()
	void OnViewMusicListButtonClick();

	UFUNCTION()
	void OnPlayMusicButton();

	UFUNCTION()
	void UpdateProgress();
};


