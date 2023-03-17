#pragma once
#include "MapActor.h"
#include "PlaneMapActor.generated.h"

UCLASS()
class APlaneMapActor: public AMapActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FRotator PlaneRotator = FRotator(90, 0, 90);

	UPROPERTY(EditDefaultsOnly)
	FVector3d MinPosition = FVector3d(-100, 0, 0);

	UPROPERTY(EditDefaultsOnly)
	FVector3d MaxPosition = FVector3d(-15, 200, 200);
	
	double PlaneSize = 200;

	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght) override;
	
	virtual FVector2d GetMapPosition(FVector3d WorldPosition) override;

	virtual FVector3d GetWorldPosition(FVector2d MapPosition) override;

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition) override;
};
