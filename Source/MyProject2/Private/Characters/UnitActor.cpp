
#include "Characters/UnitActor.h"

#include "Components/WidgetComponent.h"
#include "Military/Instances/Units/Unit.h"
#include "Widgets/Military/Map/UnitInformationListWidget.h"

AUnitActor::AUnitActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));

	WidgetComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	//SetMobility(EComponentMobility::Movable);
}

// TODO: Think of way to customise UnitMesh depending on units 
void AUnitActor::Init(const FVector3d& Position)
{
	SetActorLocation(Position);

	WidgetComponent->InitWidget();
	GetWidget<UUnitInformationListWidget>()->SetVisibility(ESlateVisibility::Hidden);

	StaticMeshComponent->SetVisibility(false);
}

void AUnitActor::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);

	UpdateWidgetVisibility();
	
	GetWidget<UUnitInformationListWidget>()->AddUnit(Unit);
}

void AUnitActor::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);

	UpdateWidgetVisibility();
	
	GetWidget<UUnitInformationListWidget>()->RemoveUnit(Unit);
}

void AUnitActor::UpdateWidgetVisibility() const
{
	if (Units.Num() == 0)
	{
		StaticMeshComponent->SetVisibility(false);
		GetWidget<UUnitInformationListWidget>()->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Units.Num() == 1)
	{
		StaticMeshComponent->SetVisibility(true);
		GetWidget<UUnitInformationListWidget>()->SetVisibility(ESlateVisibility::Visible);
	}
}
