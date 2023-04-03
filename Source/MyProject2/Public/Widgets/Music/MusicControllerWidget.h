#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Music/Description/SongDescription.h"
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
	
	virtual void NativeConstruct() override;
	
	void AddSong(FSongDescription* SongDescription);

	void Select(USongDescriptionWidget* SongDescriptionWidget);
private:
	UPROPERTY()
	TMap<FName, USongsGroupWidget*> Groups;
	
	FTimerHandle TimerHandle;

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
