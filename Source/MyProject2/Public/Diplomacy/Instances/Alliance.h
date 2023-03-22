#pragma once
#include "Alliance.generated.h"

class UCountry;

UCLASS()
class UAlliance: public UObject
{
	GENERATED_BODY()
public:
	void Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName, const TArray<UCountry*>& InvitedCountries);

	void Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName);

	void AddMember(UCountry* Country);

	void RemoveMember(UCountry* Country);

	const FText& GetName() const;

	FColor GetColor() const;

	bool IsCountryMember(UCountry* Country) const;

	UCountry* GetLeader() const;

	bool IsCountryLeader(UCountry* Country) const;

	void Dissolve();

	int Size() const;
private:
	FText AllianceName;

	UPROPERTY()
	UCountry* AllianceLeader;

	UPROPERTY()
	TArray<UCountry*> Members;
};
