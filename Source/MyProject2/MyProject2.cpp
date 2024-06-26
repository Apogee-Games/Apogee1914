// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyProject2, "MyProject2" );

FGlobalUIDelegates::FOnCountrySelected FGlobalUIDelegates::OnCountrySelected;
FGlobalUIDelegates::FOnProvinceSelected FGlobalUIDelegates::OnProvinceSelected;
FGlobalUIDelegates::FOnWarSelected FGlobalUIDelegates::OnWarSelected;