#include "Actions/ConditionCheckers/DatePassedConditionChecker.h"

#include "Kismet/KismetStringLibrary.h"

FDatePassedConditionChecker::FDatePassedConditionChecker(UInGameTime* GameTime): GameTime(GameTime)
{
}

bool FDatePassedConditionChecker::Check(const TMap<FName, FString>& Values)
{
	const FDateTime ProvidedDate = FDateTime(UKismetStringLibrary::Conv_StringToInt(Values["Year"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Month"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Day"]),
	                                         UKismetStringLibrary::Conv_StringToInt(Values["Hour"]));
	return ProvidedDate > GameTime->GetTime();
}
