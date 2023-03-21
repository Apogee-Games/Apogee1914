#pragma once
#include "Diplomacy/Instances/Alliance.h"

class IAllianceCreationObserver
{
public:
	virtual ~IAllianceCreationObserver() = default;
	virtual void AllianceWasCreated(UAlliance* Alliance) = 0;
};
