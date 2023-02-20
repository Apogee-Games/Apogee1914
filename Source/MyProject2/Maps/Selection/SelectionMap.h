#pragma once
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "SelectionMap.generated.h"

UCLASS()
class USelectionMap : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UProvince* SelectProvince(const FVector2d& Point);
	
	UProvince* GetProvince(const FVector2d& Point) const;
	
	FColor GetProvinceColor(const FVector2d& Point) const;

private:
	UPROPERTY()
	UTexture2D* SelectionMapTexture;

	FVector2D SizeVector;
	
	const FColor SelectedProvinceColor = FColor(75, 75, 150);

	const FColor NonSelectedProvinceColor = FColor(0, 0, 0);

	FColor SelectedProvince = FColor(0, 0, 0);

	void SelectProvince(const FColor& Color);
};
