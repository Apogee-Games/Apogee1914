#pragma once
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "ProvinceActor.generated.h"

class UUnitInformationListWidget;
class UUnit;

UCLASS()
class AProvinceActor: public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* ProvinceNameRenderer;

	UPROPERTY(EditDefaultsOnly)
	float LenghtScale = 1;
	
	AProvinceActor();
	
	void Init(const FText& ProvinceName, FVector2d TopLeft, FVector2d BottomRight);

	void AddAttacker(UUnit* Unit);

	void AddDefender(UUnit* Unit);

	void RemoveAttacker(UUnit* Unit);

	void RemoveDefender(UUnit* Unit);
	
	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
private:
	UPROPERTY()
	TArray<UUnit*> Units;
	
	template <class T>
	T* GetWidget() const;

	UPROPERTY()
	UUnitInformationListWidget* Widget;
	
	void UpdateWidgetVisibility() const;
};

template <class T>
T* AProvinceActor::GetWidget() const
{
	return Cast<T>(WidgetComponent->GetWidget());
}
