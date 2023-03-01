#include "UnitActor.h"

#include "Components/WidgetComponent.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "MyProject2/Widgets/Military/Units/UnitInformationListWidget.h"

AUnitActor::AUnitActor()
{
	Component = CreateDefaultSubobject<UWidgetComponent>("Widget");
	SetMobility(EComponentMobility::Movable);
	Component->SetWidgetSpace(EWidgetSpace::Screen);
	Component->RegisterComponentWithWorld(GetWorld());
	Component->SetDrawSize(FVector2d(50, 50));
}

// TODO: Think of way to customise UnitMesh depending on units 
void AUnitActor::Init(const FVector3d& ObjectScale, const FVector3d& Position, UStaticMesh* UnitMesh,
                      const TSubclassOf<UUnitInformationListWidget>& UnitInformationListWidgetClass)
{
	GetStaticMeshComponent()->SetStaticMesh(UnitMesh);
	SetActorScale3D(ObjectScale);
	SetActorLocation(Position);


	Component->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Widget = CreateWidget<UUnitInformationListWidget>(GetWorld(), UnitInformationListWidgetClass);
	Component->SetWidget(Widget);

	GetStaticMeshComponent()->SetVisibility(false);
	Widget->SetVisibility(ESlateVisibility::Hidden);
}

void AUnitActor::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);

	UpdateWidgetVisibility();
	
	Widget->AddUnit(Unit);
}

void AUnitActor::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);

	UpdateWidgetVisibility();
	
	Widget->RemoveUnit(Unit);
}

void AUnitActor::UpdateWidgetVisibility() const
{
	if (Units.Num() == 0)
	{
		GetStaticMeshComponent()->SetVisibility(false);
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Units.Num() == 1)
	{
		GetStaticMeshComponent()->SetVisibility(true);
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}
