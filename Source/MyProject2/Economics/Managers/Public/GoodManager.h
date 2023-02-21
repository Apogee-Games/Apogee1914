#pragma once

#include "Engine/DataTable.h"
#include "MyProject2/Economics/Description/GoodDescription.h"
#include "GoodManager.generated.h"

UCLASS()
class UGoodManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FGoodDescription* GetGoodDescription(const FString& GoodName) const;
	
private:
	UPROPERTY()
	UDataTable* GoodDescriptionDataTable;
};
