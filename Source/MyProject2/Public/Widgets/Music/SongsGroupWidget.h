#pragma once
#include "SongsSubgroupWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Music/Description/SongDescription.h"
#include "SongsGroupWidget.generated.h"

UCLASS()
class USongsGroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* SongsSubgroupsScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USongsSubgroupWidget> SongsSubgroupWidgetClass; 

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GroupNameTextBlock;
	
	void Init(FName GroupName, UMusicControllerWidget* ProvidedMusicControllerWidget);
	
	void AddSong(FSongDescription* SongDescription);
private:
	UPROPERTY()
	UMusicControllerWidget* MusicControllerWidget;
	
	UPROPERTY()
	TMap<FName, USongsSubgroupWidget*> Subgroups;
};
