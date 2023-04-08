#pragma once
#include "Administration/Descriptions/FractionDescription.h"
#include "Administration/Descriptions/IdeologyDescription.h"
#include "Fraction.generated.h"

UCLASS()
class UFraction: public UObject
{
	GENERATED_BODY()
public:
	void Init(const FFractionDescription& ProvidedFractionDescription);

	UIdeologyDescription* GetIdeology() const;

	const FText& GetFractionName() const;

	int32 GetMembersNumber() const;
private:
	UPROPERTY()
	UIdeologyDescription* Ideology;

	FText FractionName;

	int32 MembersNumber;
};
