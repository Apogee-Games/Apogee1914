#pragma once
#include "MyProject2/Maps/Precalculations/Boxes/ProvincesBox.h"

class IBoxObserver
{
public:
	virtual ~IBoxObserver() = default;
	virtual void BoxWasUpdated(FProvincesBox* Box) = 0;
};
