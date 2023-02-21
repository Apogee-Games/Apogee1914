#pragma once
#include "MyProject2/Administration/Descriptions/CountryDescription.h"

#include "Country.generated.h"

UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
public:

	void Init(FCountryDescription* CountryDescription);

	const FColor& GetColor() const;

	const FName& GetName() const;

	const FName& GetTag() const;

	UTexture2D* GetFlag() const;
	
private:
	FName Name;

	FName Tag;

	FColor Color;

	UPROPERTY()
	UTexture2D* Flag = nullptr;
};
