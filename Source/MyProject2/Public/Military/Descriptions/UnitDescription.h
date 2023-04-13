#pragma once
#include "MilitaryBranchDescription.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "UnitDescription.generated.h"

UCLASS()
class UUnitDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName UnitName;
	
	UPROPERTY(EditDefaultsOnly)
	UMilitaryBranchDescription* MilitaryBranch;
	
	UPROPERTY(EditDefaultsOnly)
	bool CanTransport;

	UPROPERTY(EditDefaultsOnly)
	TMap<UGoodDescription*, int32> EquipmentRequirements;

	UPROPERTY(EditDefaultsOnly)
	int32 ManpowerRequirements;

	UPROPERTY(EditDefaultsOnly)
	float Attack;

	UPROPERTY(EditDefaultsOnly)
	float Defence;
	
	UPROPERTY(EditDefaultsOnly)
	float PersonDeathScore;
};
