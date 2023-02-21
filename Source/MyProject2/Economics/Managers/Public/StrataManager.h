#pragma once
#include "MyProject2/Economics/Description/StrataDescription.h"
#include "StrataManager.generated.h"
UCLASS()
class UStrataManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FStrataDescription* GetStrataDescription(const FString& Type) const;
	
private:
	
	UPROPERTY()
	UDataTable* StrataDescriptionDataTable;
};
