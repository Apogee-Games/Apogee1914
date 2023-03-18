#pragma once
#include "Camera/CameraComponent.h"
#include "Characters/Components/MapActor.h"
#include "Characters/Components/PlayerMovementComponent.h"
#include "Characters/StateMachine/PawnState.h"
#include "Widgets/CountrySelection/ScenarioSelectionWidget.h"

#include "CountrySelectionPawn.generated.h"

UCLASS()
class ACountrySelectionPawn: public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMapActor> MapActorClass;
	
	UPROPERTY()
	AMapActor* MapActor;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UPlayerMovementComponent* MovementComponent;

	ACountrySelectionPawn();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState);

	TSharedPtr<FPawnState> GetPawnState() const;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	TSharedPtr<FPawnState> PawnState = nullptr;

	void LeftClick();

	void RightClick();
};
