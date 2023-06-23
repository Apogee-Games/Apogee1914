#pragma once
#include "Scenario.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Interfaces/BaseManager.h"

#include "MapsSwitcher.generated.h"

UCLASS(Abstract, Blueprintable)
class UMapsSwitcher: public UBaseManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* BlankMapTexture;

	UPROPERTY(BlueprintReadOnly)
	UScenario* Scenario;

	virtual void SetScenario(UScenario* ProvidedScenario) override;

	void SelectAllianceMap(AHumanPlayerPawn* Pawn);
	
	void SelectFlagsMap(AHumanPlayerPawn* Pawn);
	
	void SelectCountriesMap(AHumanPlayerPawn* Pawn);

	void SelectRelationMap(AHumanPlayerPawn* Pawn);

	void SelectIdeologyMap(AHumanPlayerPawn* Pawn);
	
	void SetApplyProvinceOutlineMap(AHumanPlayerPawn* Pawn, bool Flag);

	void SetApplySelectionMap(AHumanPlayerPawn* Pawn, bool Flag);

	virtual ELoadStage GetLoadStage() override;
};
