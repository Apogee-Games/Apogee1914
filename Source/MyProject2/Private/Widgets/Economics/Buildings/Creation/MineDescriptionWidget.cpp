
#include "Widgets/Economics/Buildings/Creation/MineDescriptionWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Economics/Description/Buildings/FactoryDescription.h"
#include "Economics/Description/Buildings/MineDescription.h"

void UMineDescriptionWidget::Init(UBuildingDescription* ProvidedBuildingDescription)
{
	Super::Init(ProvidedBuildingDescription);
	
	UMineDescription* MineDescription = Cast<UMineDescription>(ProvidedBuildingDescription);
	
	MaxLaboursTextBlock->SetText(FText::FromString(FString::FromInt(MineDescription->MaxLabours)));
}

