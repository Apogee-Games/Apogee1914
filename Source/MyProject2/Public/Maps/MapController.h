#pragma once

#include <functional>
#include "CoreMinimal.h"
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Interfaces/BaseManager.h"
#include "MapController.generated.h"

UCLASS()
class MYPROJECT2_API UMapController : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	void SetCountriesMapAll();
	void SetAlliancesMapAll();
	void SetCountryRelationMapAll();
	void SetIdeologiesMapAll();
	
	UProvince* GetProvince(FVector2d Point);
	UProvince* SelectProvince(FVector2d Point);
	void SelectProvince(UProvince* Province);
	
	void RefreshLookUpTexture();
	
	void SetOutlineEnabled(bool InbOutlineEnabled);

	virtual ELoadStage GetLoadStage() override;
private:
	FVector2d SizeVector;
	
	TUniquePtr<FCanvas> Canvas;

	FColor SelectionHighlight;
	int32 SelectedProvinceIndex = INDEX_NONE;

	FColor NonAlignedCountryColor;
	FColor NonAlliedCountryColor;
	TMap<ERelationType, FColor> ColorsMapping;

	UPROPERTY()
	TArray<UProvince*> Provinces;
	
	std::function<FLinearColor(UProvince*)> ColorGetter;

	bool bOutlineEnabled = false;
	
	void Clear();

	void Init(UScenario* Scenario);

	void DrawProvincesIdsMap(UTextureRenderTarget2D* ProvincesIdsLookUpTexture);
};
