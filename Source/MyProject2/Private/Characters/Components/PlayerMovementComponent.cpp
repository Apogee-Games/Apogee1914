#include "Characters/Components/PlayerMovementComponent.h"

void UPlayerMovementComponent::Init(AMapActor* ProvidedMapActor)
{
	MapActor = ProvidedMapActor;
}

void UPlayerMovementComponent::Move(float DeltaTime)
{
	if (MovementDirection == FVector(0, 0, 0) && RotationDirection == FRotator(0, 0, 0))
	{
		return;
	}

	FVector Position = MapActor->GetNewPosition(GetOwner()->GetActorLocation(), MovementDirection, DeltaTime);
	FQuat Rotation = MapActor->GetNewRotation(GetOwner()->GetActorLocation(), Position, GetOwner()->GetActorQuat());

	GetOwner()->SetActorLocation(Position);
	GetOwner()->SetActorRotation(Rotation);
}

void UPlayerMovementComponent::Scroll(float Value)
{
	MovementDirection.X = FMath::Clamp(Value, -1, 1);
	RotationDirection.Pitch = FMath::Clamp(Value, -1, 1);
}

void UPlayerMovementComponent::MoveUp(float Value)
{
	MovementDirection.Y = FMath::Clamp(Value, -1.f, 1.f);
}

void UPlayerMovementComponent::MoveRight(float Value)
{
	MovementDirection.Z = FMath::Clamp(Value, -1.f, 1.f);
}