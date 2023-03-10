#pragma once
#include "Maps/Precalculations/Boxes/ProvincesBox.h"

class IBoxObserver
{
public:
	virtual ~IBoxObserver() = default;
	virtual void BoxWasUpdated(const TSharedPtr<FProvincesBox>& Box) = 0;
};
