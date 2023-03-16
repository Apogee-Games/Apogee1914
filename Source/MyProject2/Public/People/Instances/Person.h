#pragma once
#include "People/Description/PersonDescription.h"

#include "Person.generated.h"

UCLASS()
class UPerson : public UObject
{
	GENERATED_BODY()
public:

	void Init(const FPersonDescription* Description);

	int32 GetAge() const;

	FName GetPersonName() const;

	const TArray<FName>& GetProfessions() const;

	UTexture2D* GetImage() const;

private:
	FDateTime DateOfBirth;

	FName PersonName;

	TArray<FName> Professions;

	UPROPERTY()
	UTexture2D* Image;
};
