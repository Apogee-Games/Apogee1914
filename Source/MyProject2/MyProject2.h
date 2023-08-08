// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

struct FGlobalUIDelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCountrySelected, UCountry*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProvinceSelected, UProvince*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWarSelected, UWar*)
	
	static FOnCountrySelected OnCountrySelected;
	static FOnProvinceSelected OnProvinceSelected;
	static FOnWarSelected OnWarSelected;
};
