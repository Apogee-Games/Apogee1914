
#include "Characters/ProvinceActor.h"

#include "Components/WidgetComponent.h"
#include "Military/Instances/Units/Unit.h"
#include "Widgets/Military/Map/UnitInformationListWidget.h"

AProvinceActor::AProvinceActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));

	WidgetComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	//SetMobility(EComponentMobility::Movable);
}

// TODO: Think of way to customise UnitMesh depending on units 
void AProvinceActor::Init()
{
	WidgetComponent->InitWidget();
	GetWidget<UUnitInformationListWidget>()->SetVisibility(ESlateVisibility::Hidden);

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
	
	GetWidget<UUnitInformationListWidget>()->AddUnit(Unit);
}

void AProvinceActor::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);

	UpdateWidgetVisibility();
	
	GetWidget<UUnitInformationListWidget>()->RemoveUnit(Unit);
}

void AProvinceActor::UpdateWidgetVisibility() const
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
