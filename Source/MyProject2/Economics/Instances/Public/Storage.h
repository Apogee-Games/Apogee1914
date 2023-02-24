#pragma once
#include "MyProject2/Economics/Description/GoodDescription.h"

#include "Storage.generated.h"

enum EStorageType
{
	Country,
	LowerStrata,
	MiddleStrata,
	UpperStrata
};


UCLASS()
class UStorage: public UObject
{
	GENERATED_BODY()
public:

	void Init(const EStorageType& ProvidedType);
	
	void Init(const FName& StrataType);

	void Supply(const FName& Good, const int32 Amount);

	int32 Estimate(const FName& Good, const int32 Amount);

	int32 GetGoodAmount(const FName& Good) const;
	
	int32 Demand(const FName& Good, const int32 Amount);

private:
	TMap<FName, int32> Goods;

	EStorageType Type = EStorageType::Country;
	
	inline static TMap<FName, EStorageType> StrataTypeToStorageType = {
		{"LOW", EStorageType::LowerStrata},
		{"MIDDLE", EStorageType::MiddleStrata},
		{"UPPER", EStorageType::UpperStrata}
	};
};
