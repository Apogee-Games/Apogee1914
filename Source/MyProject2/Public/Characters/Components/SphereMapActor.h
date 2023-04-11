#pragma once
#include "MapActor.h"
#include "SphereMapActor.generated.h"

UCLASS()
class ASphereMapActor : public AMapActor
{
	GENERATED_BODY()

public:
	float Radius = -1;

	UPROPERTY(EditDefaultsOnly)	
	FVector3d SphereCenter = FVector3d(159, 95, 81);

	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght) override;

	virtual FVector2d GetMapPosition(FVector3d WorldPosition) override;

	virtual FVector3d GetWorldPosition(FVector2d MapPosition) override;

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition) override;
};
