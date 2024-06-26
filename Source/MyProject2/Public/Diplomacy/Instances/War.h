﻿#pragma once
#include "War.generated.h"

class UCountry;

UCLASS()
class UWar: public UObject
{
	GENERATED_BODY()
public:
	void Init(UCountry* ProvidedAttackerLeader, UCountry* ProvidedDefenderLeader);

	void AddAttacker(UCountry* Country);

	void AddDefender(UCountry* Country);

	UCountry* GetAttackerLeader() const;

	UCountry* GetDefenderLeader() const;

	const TArray<UCountry*>& GetAttackers() const;

	const TArray<UCountry*>& GetDefenders() const;

	bool IsMember(UCountry* Country) const;

	void AddCountryOnSide(UCountry* Country, UCountry* OnSideOfCountry);

	void End();
private:
	UPROPERTY()
	UCountry* AttackerLeader;

	UPROPERTY()
	TArray<UCountry*> Attackers;

	UPROPERTY()
	UCountry* DefenderLeader;

	UPROPERTY()
	TArray<UCountry*> Defenders;
};
