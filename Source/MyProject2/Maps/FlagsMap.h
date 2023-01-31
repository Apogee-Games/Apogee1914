#pragma once

#include "FlagsMap.generated.h"

UCLASS()
class UFlagsMap: public UWorldSubsystem
{
public:
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void UpdateFlagsMapColors();

private:
	UPROPERTY()
	UTexture2D* FlagsMapTexture;

	UPROPERTY()	
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;
	
	TMap<FString, FVector4> FindCountriesBoxes(const FColor* ProvincesColors);

	static FVector2d GetRelativePosition(const FVector2d& Position, const FVector4& Box);

	static FColor GetFlagColor(UTexture2D* Flag, const FVector2d& RelativePosition);

	FVector4 UpdateBox(const FVector4& Box, const FVector2d& Position);
};
