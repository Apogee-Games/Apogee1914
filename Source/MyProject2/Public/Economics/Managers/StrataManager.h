﻿#pragma once
#include "Economics/Description/StrataDescription.h"
#include "StrataManager.generated.h"
UCLASS()
class UStrataManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FStrataDescription* GetStrataDescription(const FName& Type) const;
	
private:
	UPROPERTY()
	UDataTable* StrataDescriptionDataTable;
};
