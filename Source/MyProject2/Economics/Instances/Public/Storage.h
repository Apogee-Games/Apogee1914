#pragma once
#include "Good.h"
#include "MyProject2/Economics/Interfaces/Observables/StorageObservable.h"

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

	void Supply(const FName& GoodName, const int32 Amount);

	int32 Estimate(const FName& GoodName, const int32 Amount);

	int32 GetGoodAmount(const FName& GoodName) const;
	
	int32 Demand(const FName& GoodName, const int32 Amount);

	EStorageType GetType() const;

private:
	TMap<FName, UGood*> Goods;

	EStorageType Type = EStorageType::Country;
	
	inline static TMap<FName, EStorageType> StrataTypeToStorageType = {
		{"LOW", EStorageType::LowerStrata},
		{"MIDDLE", EStorageType::MiddleStrata},
		{"UPPER", EStorageType::UpperStrata}
	};
};
