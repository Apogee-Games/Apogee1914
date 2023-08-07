// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Administration/Instances/Country.h"

struct FGlobalUIDelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCountrySelected, UCountry*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProvinceSelected, UProvince*)
	
	static FOnCountrySelected OnCountrySelected;
	static FOnProvinceSelected OnProvinceSelected;
};
