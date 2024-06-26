#pragma once

#include "MapActor.generated.h"

class AHumanPlayerPawn;
UCLASS()
class AMapActor: public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MapsStaticMeshComponent;

	AMapActor();

	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, FRotator Rotation, float Lenght);

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition, FQuat Rotation);
	
	virtual FVector2d GetMapPosition(APawn* Pawn);
	
	virtual FVector2d GetMapPosition(FVector3d WorldPosition);

	virtual FVector3d GetWorldPosition(FVector2d MapPosition);
};
