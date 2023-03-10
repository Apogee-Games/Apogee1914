#pragma once
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "UnitActor.generated.h"

class UUnit;

UCLASS()
class AUnitActor: public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	
	AUnitActor();
	
	void Init(const FVector3d& Position);

	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
private:
	TArray<UUnit*> Units;
	
	template <class T>
	T* GetWidget() const;

	void UpdateWidgetVisibility() const;
};

template <class T>
T* AUnitActor::GetWidget() const
{
	return Cast<T>(WidgetComponent->GetWidget());
}
