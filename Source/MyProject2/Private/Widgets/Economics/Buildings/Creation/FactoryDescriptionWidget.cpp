
#include "Widgets/Economics/Buildings/Creation/FactoryDescriptionWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Economics/Description/Buildings/FactoryDescription.h"

void UFactoryDescriptionWidget::Init(UBuildingDescription* ProvidedBuildingDescription)
{
	Super::Init(ProvidedBuildingDescription);
	
	UFactoryDescription* FactoryDescription = Cast<UFactoryDescription>(ProvidedBuildingDescription);
	
	MaxLaboursTextBlock->SetText(FText::FromString(FString::FromInt(FactoryDescription->MaxLabours)));
}

