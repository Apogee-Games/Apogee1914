#pragma once
#include "Administration/Descriptions/IdeologyDescription.h"
#include "Ideology.generated.h"

UCLASS()
class UIdeology: public UObject
{
	GENERATED_BODY()
public:
	void Init(FIdeologyDescription* IdeologyDescription);

	const FName& GetTag() const;

	const FText& GetName() const;

	const FColor& GetColor() const;
private:
	FName Tag;

	FText Name;

	FColor Color;
};
