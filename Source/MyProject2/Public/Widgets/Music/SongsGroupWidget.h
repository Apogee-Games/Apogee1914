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
	
	void Init(USongsGroup* SongsGroup, UMusicControllerWidget* ProvidedMusicControllerWidget);
private:
	UPROPERTY()
	UMusicControllerWidget* MusicControllerWidget;
};
