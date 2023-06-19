#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
#include "OutlineMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UOutlineMap: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	void CreateOutline();

	virtual ELoadStage GetLoadStage() override;

	UPROPERTY(EditDefaultsOnly)
	FColor OutlineColor = FColor(0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly)
	FColor BackgroundColor = FColor(255, 255, 255);
private:
	UPROPERTY()
	UTexture2D* OutlinesMapTexture;
	
	FVector2D SizeVector;

	void Clear();

	void Init(UScenario* Scenario);
};
