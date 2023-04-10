#pragma once
#include "StoredGood.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "Economics/Interfaces/Observables/StorageObservable.h"

#include "Storage.generated.h"

UENUM()
enum class EStorageType: uint8
{
	Country,
	LowerStrata,
	MiddleStrata,
	UpperStrata
};


UCLASS()
class UStorage: public UObject, public IStorageObservable
{
	GENERATED_BODY()
public:
	void Init(EStorageType ProvidedType);
	
	void Init(const FName& StrataType);

	void Supply(UGoodDescription* Good, const int32 Amount);

	float Estimate(UGoodDescription* Good, const int32 Amount);

	float GetGoodAmount(UGoodDescription* GoodN) const;
	
	float Demand(UGoodDescription* Good, const int32 Amount);

	EStorageType GetType() const;
private:
	UPROPERTY()
	TMap<UGoodDescription*, UStoredGood*> Goods;

	EStorageType Type = EStorageType::Country;

	void AddGoodIfNotPresent(UGoodDescription* Good);
	
	inline static TMap<FName, EStorageType> StrataTypeToStorageType = {
		{"LOW", EStorageType::LowerStrata},
		{"MIDDLE", EStorageType::MiddleStrata},
		{"UPPER", EStorageType::UpperStrata}
	};
};
