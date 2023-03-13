#pragma once

#include "MapActor.generated.h"

class AHumanPlayerPawn;
UCLASS()
class AMapActor: public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TerrainStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MapsStaticMeshComponent;

	AMapActor();
	
	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght);

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition);
	
	virtual FVector2d GetMapPosition(AHumanPlayerPawn* Pawn);
	
	virtual FVector2d GetMapPosition(FVector3d WorldPosition);

	virtual FVector3d GetWorldPosition(FVector2d MapPosition);
};
