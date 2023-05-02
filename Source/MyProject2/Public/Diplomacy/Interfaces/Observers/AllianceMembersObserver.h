#pragma once
#include "Diplomacy/Instances/Alliance.h"

class IAllianceMembersObserver
{
public:
	virtual ~IAllianceMembersObserver() = default;
	virtual void CountryHasJoinedAlliance(UCountry* Country) = 0;
};