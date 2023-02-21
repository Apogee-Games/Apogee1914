#include "../Public/StrataManager.h"

#include "Engine/DataTable.h"

void UStrataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	StrataDescriptionDataTable
			= LoadObject<UDataTable>(nullptr,TEXT("/Game/Sources/strata_description"));
	
}

FStrataDescription* UStrataManager::GetStrataDescription(const FName& Type) const
{
	return reinterpret_cast<FStrataDescription*>(StrataDescriptionDataTable->FindRowUnchecked(Type));
}

