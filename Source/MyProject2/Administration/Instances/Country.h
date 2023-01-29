#pragma once
#include "MyProject2/Administration/Descriptions/CountryDescription.h"

#include "Country.generated.h"

UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
public:

	void Init(FCountryDescription* CountryDescription);

	const FColor* GetColor();

	const FString& GetName();

	const FString& GetTag() const;
	
private:
	FString Name;

	FString Tag;

	FColor Color;
	
};
