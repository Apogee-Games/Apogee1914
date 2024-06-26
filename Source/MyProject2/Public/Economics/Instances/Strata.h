﻿#pragma once
#include "Market.h"
#include "Storage.h"
#include "Economics/Description/StrataDescription.h"
#include "Strata.generated.h"

UCLASS()
class UStrata : public UObject
{
	GENERATED_BODY()

public:
	UStrata();

	void Init(const FName& ProvidedType);

	UStorage* GetStorage() const;

	// TODO: Maybe tie Country in future

private:
	UPROPERTY()
	UStorage* Storage;
	
	UPROPERTY()
	UMarket* StrataMarket;

	UPROPERTY()
	FName Type;
};