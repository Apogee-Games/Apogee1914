#include "Widgets/Music/SongsSubgroupWidget.h"

void USongsSubgroupWidget::Init(USongsSubgroup* SongsSubgroup, UMusicControllerWidget* ProvidedMusicControllerWidget)
{
	SubgroupNameTextBlock->SetText(SongsSubgroup->Name);
	MusicControllerWidget = ProvidedMusicControllerWidget;
	for (const auto& Song: SongsSubgroup->Songs)
	{
		USongDescriptionWidget* SongDescriptionWidget = CreateWidget<USongDescriptionWidget>(GetOwningPlayer(), SongDescriptionWidgetClass);
		SongDescriptionWidget->Init(Song, MusicControllerWidget);
		SongsDescriptionsScrollBox->AddChild(SongDescriptionWidget);
	}
}
