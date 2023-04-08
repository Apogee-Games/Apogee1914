#pragma once
#include "People/Description/PersonDescription.h"

#include "Person.generated.h"

UCLASS()
class UPerson : public UObject
{
	GENERATED_BODY()
public:
	void Init(UPersonDescription* Description);

	int32 GetAge() const;

	const FText& GetPersonName() const;

	const TArray<UProfessionDescription*>& GetProfessions() const;

	UTexture2D* GetImage() const;
private:
	FDateTime DateOfBirth;

	FText Name;

	UPROPERTY()
	TArray<UProfessionDescription*> Professions;

	UPROPERTY()
	UTexture2D* Image;
};
