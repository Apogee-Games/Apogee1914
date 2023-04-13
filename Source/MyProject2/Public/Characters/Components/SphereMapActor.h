#pragma once
#include "MapActor.h"
#include "SphereMapActor.generated.h"

UCLASS()
class ASphereMapActor : public AMapActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float Radius = 1281.04114;

	UPROPERTY(EditDefaultsOnly)	
	FVector3d SphereCenter = FVector3d(159, 95, 81);

	UPROPERTY(EditDefaultsOnly)
	FRotator SphereRotation = FRotator(0, 100, 30);

	UPROPERTY(EditDefaultsOnly)
	FVector3d SpeedVector = FVector3d(100, 100, 100);
	
	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, FRotator Rotation, float DeltaTime) override;

	virtual FVector2d GetMapPosition(FVector3d WorldPosition) override;

	virtual FVector3d GetWorldPosition(FVector2d MapPosition) override;

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition, FQuat Rotation) override;
};
