#include "Widgets/Music/SongsGroupWidget.h"

void USongsGroupWidget::Init(FName GroupName, UMusicControllerWidget* ProvidedMusicControllerWidget)
{
	GroupNameTextBlock->SetText(FText::FromName(GroupName));
	MusicControllerWidget = ProvidedMusicControllerWidget;
}

void USongsGroupWidget::AddSong(FSongDescription* SongDescription)
{
	if (!Subgroups.Contains(SongDescription->Subgroup))
	{
		USongsSubgroupWidget* SongsSubgroupWidget = CreateWidget<USongsSubgroupWidget>(GetOwningPlayer(), SongsSubgroupWidgetClass);
		SongsSubgroupWidget->Init(SongDescription->Subgroup, MusicControllerWidget);
		SongsSubgroupsScrollBox->AddChild(SongsSubgroupWidget);
		Subgroups.Add(SongDescription->Subgroup, SongsSubgroupWidget);
	}
	Subgroups[SongDescription->Subgroup]->AddSong(SongDescription);
}
