#pragma once
#include "SongDescriptionWidget.h"
#include "Blueprint/UserWidget.h"
#include "SongsSubgroupWidget.generated.h"

class UMusicControllerWidget;

UCLASS()
class USongsSubgroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USongDescriptionWidget> SongDescriptionWidgetClass; 

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* SongsDescriptionsScrollBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SubgroupNameTextBlock;
	
	void Init(USongsSubgroup* SongsSubgroup, UMusicControllerWidget* ProvidedMusicControllerWidget);
private:
	UPROPERTY()
	UMusicControllerWidget* MusicControllerWidget;
};
