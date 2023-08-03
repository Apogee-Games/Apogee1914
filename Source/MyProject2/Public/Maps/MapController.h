#pragma once

#include <functional>
#include "CoreMinimal.h"
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Interfaces/BaseManager.h"
#include "MapController.generated.h"

UENUM(BlueprintType)
enum class EMapMode : uint8
{
	None,
	CountriesMap,
	AlliancesMap,
	RelationsMap,
	IdeologiesMap
};

ENUM_RANGE_BY_FIRST_AND_LAST(EMapMode, EMapMode::None, EMapMode::IdeologiesMap)

UCLASS()
class MYPROJECT2_API UMapController : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	void SetMapMode(EMapMode MapMode);
	
	void SetCountriesMapAll();
	void SetAlliancesMapAll();
	void SetCountryRelationMapAll();
	void SetIdeologiesMapAll();
	
	UProvince* GetProvince(FVector2d Point);
	UProvince* SelectProvince(FVector2d Point);
	void SelectProvince(UProvince* Province);
	
	void RefreshLookUpTexture();
	
	void SetOutlineEnabled(bool InbOutlineEnabled);

	int32 GetSelectedMapItem() const { return SelectedMapItem; }
	void SetSelectedMapItem(int32 InSelectedMapItem) { SelectedMapItem = InSelectedMapItem; }

	TArray<EMapMode>& GetMapItems() { return MapItems; }
	
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
	
	TFunction<FLinearColor(UProvince*)> ColorGetter;

	TArray<EMapMode> MapItems;
	int32 SelectedMapItem = 0;

	bool bOutlineEnabled = false;
	
	void Clear();

	void Init(UScenario* Scenario);

	void DrawProvincesIdsMap(UTextureRenderTarget2D* ProvincesIdsLookUpTexture);
};
