#pragma once
#include "Ideology.h"
#include "Administration/Descriptions/FractionDescription.h"
#include "Fraction.generated.h"

UCLASS()
class UFraction: public UObject
{
	GENERATED_BODY()
public:
	void Init(const FFractionDescription& ProvidedFractionDescription);

	UIdeology* GetIdeology() const;

	const FText& GetFractionName() const;

	int32 GetMembersNumber() const;
private:
	UPROPERTY()
	UIdeology* Ideology;

	FText FractionName;

	int32 MembersNumber;
};
