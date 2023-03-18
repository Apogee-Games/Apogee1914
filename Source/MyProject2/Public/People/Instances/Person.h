#pragma once
#include "People/Description/PersonDescription.h"

#include "Person.generated.h"

UCLASS()
class UPerson : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FName& ProvidedId, const FPersonDescription* Description);

	const FName& GetId() const;
	
	int32 GetAge() const;

	FName GetPersonName() const;

	const TArray<FName>& GetProfessions() const;

	UTexture2D* GetImage() const;
private:
	FName Id;
	
	FDateTime DateOfBirth;

	FName PersonName;

	TArray<FName> Professions;

	UPROPERTY()
	UTexture2D* Image;
};
