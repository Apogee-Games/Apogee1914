#pragma once
#include "MusicControllerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableText.h"
#include "Components/TextBlock.h"
#include "Music/Description/SongDescription.h"
#include "SongDescriptionWidget.generated.h"

UCLASS()
class USongDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SongNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* WrittenByTextBlock;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SungByTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UMultiLineEditableText* SongDescriptionEditableTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;
	
	void Init(FSongDescription* ProvidedSongDescription, UMusicControllerWidget* ProvidedMusicControllerWidget);

	void Select();

	void UnSelect();

	FSongDescription* GetSongDescription();
private:
	FSongDescription* SongDescription;
	
	UPROPERTY()
	UMusicControllerWidget* MusicControllerWidget;
	
	UFUNCTION()
	void OnButtonClick();
};
