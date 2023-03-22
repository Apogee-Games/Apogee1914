#pragma once
#include "Administration/Instances/Country.h"

#include "Alliance.generated.h"

UCLASS()
class UAlliance: public UObject
{
	GENERATED_BODY()
public:
	void Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName);

	void AddMember(UCountry* Country);

	void RemoveMember(UCountry* Country);

	const FText& GetName() const;

	FColor GetColor() const;

	bool IsCountryMember(UCountry* Country) const;
private:
	FText AllianceName;

	UPROPERTY()
	UCountry* AllianceLeader;

	UPROPERTY()
	TArray<UCountry*> Members;
};
