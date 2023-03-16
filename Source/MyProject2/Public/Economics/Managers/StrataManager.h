#pragma once
#include "Economics/Description/StrataDescription.h"
#include "StrataManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStrataManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	FStrataDescription* GetStrataDescription(const FName& Type) const;
private:
	UPROPERTY()
	UDataTable* StrataDescriptionDataTable;
};
