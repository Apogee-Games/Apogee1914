#include "Widgets/Music/SongDescriptionWidget.h"

void USongDescriptionWidget::Init(USongDescription* ProvidedSongDescription, UMusicControllerWidget* ProvidedMusicControllerWidget)
{
	SongDescription = ProvidedSongDescription;
	SongNameTextBlock->SetText(SongDescription->Name);
	WrittenByTextBlock->SetText(SongDescription->WrittenBy);
	SungByTextBlock->SetText(SongDescription->SungBy);
	SongDescriptionEditableTextBlock->SetText(SongDescription->Description);

	Button->OnClicked.AddDynamic(this, &USongDescriptionWidget::OnButtonClick);

	MusicControllerWidget = ProvidedMusicControllerWidget;
}

void USongDescriptionWidget::Select()
{
	Button->SetIsEnabled(false);
}

void USongDescriptionWidget::UnSelect()
{
	Button->SetIsEnabled(true);
}

USongDescription* USongDescriptionWidget::GetSongDescription()
{
	return SongDescription;
}

void USongDescriptionWidget::OnButtonClick()
{
	MusicControllerWidget->Select(this);
}
