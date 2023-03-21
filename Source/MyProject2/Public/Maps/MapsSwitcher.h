#pragma once
#include "Scenario.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

#include "MapsSwitcher.generated.h"

UCLASS(Abstract, Blueprintable)
class UMapsSwitcher: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* BlankMapTexture;

	UPROPERTY(BlueprintReadOnly)
	UScenario* Scenario;
	
	void SetScenario(UScenario* ProvidedScenario);

	void SelectFlagsMap(AHumanPlayerPawn* Pawn);

	void SelectCountriesMap(AHumanPlayerPawn* Pawn);

	void SelectRelationMap(AHumanPlayerPawn* Pawn);

	void SetApplyProvinceOutlineMap(AHumanPlayerPawn* Pawn, bool Flag);

	void SetApplySelectionMap(AHumanPlayerPawn* Pawn, bool Flag);
};
