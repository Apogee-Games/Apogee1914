#pragma once

#include "Characters/Components/MapActor.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Kismet/KismetSystemLibrary.h"

AMapActor::AMapActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	TerrainStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terrain"));
	TerrainStaticMeshComponent->SetupAttachment(RootComponent);
	
	MapsStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Maps"));
	MapsStaticMeshComponent->SetupAttachment(RootComponent);
}

void AMapActor::BeginPlay()
{
	Super::BeginPlay();
	TerrainMapMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(TerrainMapMaterialInterface, this);
	TerrainStaticMeshComponent->SetMaterial(0, TerrainMapMaterialInstanceDynamic);

	MapsMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MapsMaterialInterface, this);
	MapsStaticMeshComponent->SetMaterial(0, MapsMaterialInstanceDynamic);
}

FVector3d AMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, FRotator Rotation, float Lenght)
{
	return FVector3d(0, 0, 0);
}

FQuat AMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition, FQuat Rotation)
{
	return FQuat(0, 0, 0, 0);
}

FVector2d AMapActor::GetMapPosition(APawn* Pawn)
{
	FVector Location, Direction;
	Pawn->GetController<APlayerController>()->DeprojectMousePositionToWorld(Location, Direction);
	
	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingle(
		this,
		Location,
		Location + 10000 * Direction,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		false,
		{},
		EDrawDebugTrace::None,
		HitResult,
		false);

	return GetMapPosition(HitResult.Location);
}

FVector2d AMapActor::GetMapPosition(FVector3d WorldPosition)
{
	return FVector2d(WorldPosition.Y, WorldPosition.Z);
}

FVector3d AMapActor::GetWorldPosition(FVector2d MapPosition)
{
	return FVector3d(MapPosition.X, MapPosition.Y, 0.0);
}
