#include "Widgets/Music/SongsSubgroupWidget.h"

void USongsSubgroupWidget::Init(FName SubgroupName, UMusicControllerWidget* ProvidedMusicControllerWidget)
{
	SubgroupNameTextBlock->SetText(FText::FromName(SubgroupName));
	MusicControllerWidget = ProvidedMusicControllerWidget;
}

void USongsSubgroupWidget::AddSong(FSongDescription* SongDescription)
{
	USongDescriptionWidget* SongDescriptionWidget = CreateWidget<USongDescriptionWidget>(GetOwningPlayer(), SongDescriptionWidgetClass);
	SongDescriptionWidget->Init(SongDescription, MusicControllerWidget);
	SongsDescriptionsScrollBox->AddChild(SongDescriptionWidget);
}
