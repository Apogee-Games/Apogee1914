#pragma once
#include "MapActor.h"
#include "PlayerMovementComponent.generated.h"

UCLASS()
class UPlayerMovementComponent: public UActorComponent
{
	GENERATED_BODY()
public:
	void Init(AMapActor* ProvidedMapActor);
	
	void MoveUp(float Value);

	void MoveRight(float Value);

	void Move(float DeltaTime);

	void Scroll(float Value);
private:
	FVector MovementDirection = FVector(0, 0, 0);

	FRotator RotationDirection = FRotator(0, 0, 0);
	
	UPROPERTY()
	AMapActor* MapActor;
};