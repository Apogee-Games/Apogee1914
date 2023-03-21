#pragma once
#include "MapActor.h"
#include "SphereMapActor.generated.h"

UCLASS()
class  ASphereMapActor : public AMapActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FRotator SphereRotator = FRotator(90, 0, 90);	
	double SphereSize = 200;

	ASphereMapActor();
	
	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght) override;
	
	virtual FVector2d GetMapPosition(FVector3d WorldPosition) override;

	virtual FVector3d GetWorldPosition(FVector2d MapPosition) override;

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition) override;
};
