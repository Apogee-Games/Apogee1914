#pragma once
#include "Diplomacy/Instances/War.h"

class IWarDeclarationObserver
{
public:
	virtual ~IWarDeclarationObserver() = default;
	virtual void WarWasDeclared(UWar* War) = 0;
};
