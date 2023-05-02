#pragma once
#include "Diplomacy/Instances/Alliance.h"
#include "Diplomacy/Interfaces/Observers/AllianceMembersObserver.h"

class IAllianceMembersObservable
{
public:
	void NotifyMemberJoining(UCountry* Country);
	
	bool AddAllianceMembersObserver(IAllianceMembersObserver* Observer);
	
	bool RemoveAllianceMembersObserver(IAllianceMembersObserver* Observer);
private:
	TArray<IAllianceMembersObserver*> Observers;
};

