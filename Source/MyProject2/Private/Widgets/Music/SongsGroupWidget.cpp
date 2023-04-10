#include "Widgets/Music/SongsGroupWidget.h"

void USongsGroupWidget::Init(USongsGroup* SongsGroup, UMusicControllerWidget* ProvidedMusicControllerWidget)
{
	GroupNameTextBlock->SetText(SongsGroup->Name);
	MusicControllerWidget = ProvidedMusicControllerWidget;
	for (const auto& Subgroup: SongsGroup->Subgroups)
	{
		USongsSubgroupWidget* SongsSubgroupWidget = CreateWidget<USongsSubgroupWidget>(GetOwningPlayer(), SongsSubgroupWidgetClass);
		SongsSubgroupWidget->Init(Subgroup, MusicControllerWidget);
		SongsSubgroupsScrollBox->AddChild(SongsSubgroupWidget);
	}
}