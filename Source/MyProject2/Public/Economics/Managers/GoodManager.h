#pragma once

#include "Engine/DataTable.h"
#include "Economics/Description/GoodDescription.h"
#include "GoodManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UGoodManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	FGoodDescription* GetGoodDescription(const FString& GoodName) const;
private:
	UPROPERTY()
	UDataTable* GoodDescriptionDataTable;
};
