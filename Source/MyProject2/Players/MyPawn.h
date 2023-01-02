// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject2/Widgets/ProvinceData.h"
#include "MyProject2/World/MapManager.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT2_API AMyPawn : public APawn
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector SpeedVector;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	FRotator PlaneRotator = FRotator(90, 0, 90);

	UPROPERTY(EditAnywhere)
	double MinXPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxXPosition = 200;

	UPROPERTY(EditAnywhere)
	double MinYPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxYPosition = 120;

	UPROPERTY(EditAnywhere)
	double MinZPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxZPosition = 120;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProvinceData> ProvinceDataWidgetClass;

private:
	FMapManager MapManager = FMapManager("/Game/maps/provinces", "/Game/maps/province", "/Game/maps/country", "/Game/maps/outlines");

	UPROPERTY()
	UProvinceData* ProvinceDataWidget;

	const FVector PlaneNormal = FVector(1, 0, 0);
	const FVector PlaneBase = FVector(0, 0, 0);

	const UE::Math::TPlane<double> Plane = UE::Math::TPlane(PlaneBase, PlaneNormal);

	FVector MovementDirection = FVector(0, 0, 0);

	FRotator RotationDirection = FRotator(0, 0, 0);

	double PlaneSize = 200;

	void MoveUp(float Value);

	void MoveRight(float Value);

	void LeftClick();

	void Move(float DeltaTime);

	void Scroll(float Value);

	bool IsInside(const FVector& Position) const;

	FVector GetNormalizedPositionOnPlane() const;
};
