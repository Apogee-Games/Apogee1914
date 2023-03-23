#include "Maps/MapsSwitcher.h"

void UMapsSwitcher::SetScenario(UScenario* ProvidedScenario)
{
	Scenario = ProvidedScenario;
}

void UMapsSwitcher::SelectAllianceMap(AHumanPlayerPawn* Pawn)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	MapsMaterial->SetTextureParameterValue(TEXT("Front"), Scenario->AlliancesMapTexture);
}

void UMapsSwitcher::SelectFlagsMap(AHumanPlayerPawn* Pawn)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	MapsMaterial->SetTextureParameterValue(TEXT("Front"), Scenario->FlagsMapTexture);
}

void UMapsSwitcher::SelectCountriesMap(AHumanPlayerPawn* Pawn)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	MapsMaterial->SetTextureParameterValue(TEXT("Front"), Scenario->CountriesMapTexture);
}

void UMapsSwitcher::SelectRelationMap(AHumanPlayerPawn* Pawn)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	MapsMaterial->SetTextureParameterValue(TEXT("Front"), Scenario->CountryRelationMapTexture);
}

void UMapsSwitcher::SelectIdeologyMap(AHumanPlayerPawn* Pawn)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	MapsMaterial->SetTextureParameterValue(TEXT("Front"), Scenario->IdeologiesMapTexture);
}

void UMapsSwitcher::SetApplyProvinceOutlineMap(AHumanPlayerPawn* Pawn, bool Flag)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	if (Flag)
	{
		MapsMaterial->SetTextureParameterValue(TEXT("Outlines"), Scenario->OutlinesMapTexture);
	} else
	{
		MapsMaterial->SetTextureParameterValue(TEXT("Outlines"), BlankMapTexture);
	}
}

void UMapsSwitcher::SetApplySelectionMap(AHumanPlayerPawn* Pawn, bool Flag)
{
	UMaterialInstanceDynamic* MapsMaterial = Pawn->MapActor->MapsMaterialInstanceDynamic;
	if (Flag)
	{
		MapsMaterial->SetTextureParameterValue(TEXT("Selection"), Scenario->SelectionMapTexture);
	} else
	{
		MapsMaterial->SetTextureParameterValue(TEXT("Selection"), BlankMapTexture);
	}
}

