#include "MyProject2/Events/ConditionCheckers/Headers/DatePassedConditionChecker.h"

#include "Kismet/KismetStringLibrary.h"

FDatePassedConditionChecker::FDatePassedConditionChecker(FInGameTime* GameTime): GameTime(GameTime)
{
}

bool FDatePassedConditionChecker::Check(TMap<FString, FString> Values)
{
	const FDateTime ProvidedDate = FDateTime(UKismetStringLibrary::Conv_StringToInt(Values["Year"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Month"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Day"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Hour"]));
	return ProvidedDate > *GameTime->GetTime();
}