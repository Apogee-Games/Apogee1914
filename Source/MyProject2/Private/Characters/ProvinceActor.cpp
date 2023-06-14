
#include "Characters/ProvinceActor.h"

#include "Components/WidgetComponent.h"
#include "Military/Instances/Units/Unit.h"
#include "Widgets/Military/Map/UnitInformationListWidget.h"

AProvinceActor::AProvinceActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	ProvinceNameRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Provicne name renderer"));
	
	WidgetComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);
	ProvinceNameRenderer->SetupAttachment(RootComponent);

	//SetMobility(EComponentMobility::Movable);
}

// TODO: Think of way to customise UnitMesh depending on units 
void AProvinceActor::Init(const FText& ProvinceName, FVector2d TopLeft, FVector2d BottomRight)
{
	WidgetComponent->InitWidget();
	Widget = GetWidget<UUnitInformationListWidget>();
	if (Widget)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	FVector2d Box = BottomRight - TopLeft;

	float Scale = LenghtScale * Box.Length() / ProvinceName.ToString().Len();
	
	ProvinceNameRenderer->SetText(ProvinceName);
	ProvinceNameRenderer->SetWorldScale3D(FVector(1, Scale, 0.1));

	if (Box.X >= Box.Y)
	{
		FRotator Rotator = ProvinceNameRenderer->GetComponentRotation();
		Rotator.Roll = -FMath::Atan2(Box.Y, Box.X) / PI * 180;
		ProvinceNameRenderer->SetWorldRotation(Rotator);
	} else
	{
		FRotator Rotator = ProvinceNameRenderer->GetComponentRotation();
		Rotator.Roll = -FMath::Atan2(-Box.Y, Box.X) / PI * 180;
		ProvinceNameRenderer->SetWorldRotation(Rotator);
	}
	
	StaticMeshComponent->SetVisibility(false);
}

void AProvinceActor::AddAttacker(UUnit* Unit)
{
	AddUnit(Unit);
}

void AProvinceActor::AddDefender(UUnit* Unit)
{
	AddUnit(Unit);
}

void AProvinceActor::RemoveAttacker(UUnit* Unit)
{
	RemoveUnit(Unit);
}

void AProvinceActor::RemoveDefender(UUnit* Unit)
{
	RemoveUnit(Unit);
}

void AProvinceActor::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);

	UpdateWidgetVisibility();

	if (Widget) {
		Widget->AddUnit(Unit);
	}
}

void AProvinceActor::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);

	UpdateWidgetVisibility();

	if (Widget)
	{
		Widget->RemoveUnit(Unit);
	}
}

void AProvinceActor::UpdateWidgetVisibility() const
{
	if (Units.Num() == 0)
	{
		StaticMeshComponent->SetVisibility(false);
		if (Widget)
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else if (Units.Num() == 1)
	{
		StaticMeshComponent->SetVisibility(true);
		if (Widget)
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
