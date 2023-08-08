// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayablePawn.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Unit.h"
#include "Widgets/Economics/Buildings/Production/FactoryProductionWidget.h"
#include "HumanPlayerPawn.generated.h"

UENUM()
enum class EToBeInvitedCountryStatus
{
	Added,
	Removed
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCountryToBeInvitedToAllianceStatusChanged, UCountry*, EToBeInvitedCountryStatus)

UCLASS()
class MYPROJECT2_API AHumanPlayerPawn : public APlayablePawn
{
	GENERATED_BODY()
public:
	AHumanPlayerPawn();

	UPROPERTY(EditDefaultsOnly)
	UUnitsSelectionComponent* UnitSelectionComponent;
	
	UPROPERTY()
	UAudioComponent* AudioComponent;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetRuledCountry(UCountry* Country);
	const FName& GetRuledCountryTag() const;
	UCountry* GetRuledCountry() const;

	void SelectUnitDescription(UUnitDescription* UnitDescription);
	UUnitDescription* GetSelectedUnitDescription() const;

	void SelectBuildingDescription(UBuildingDescription* BuildingDescription);
	UBuildingDescription* GetSelectedBuildingDescription() const;

	void SetCommandable(ICommandable* Commandable);
	ICommandable* GetSelectedCommandable() const;

	void AddToBeInvitedCountry(UCountry* Country);
	void RemoveToBeInvitedCountry(UCountry* Country);
	TArray<UCountry*>& GetToBeInvitedCountries();
	
	void Play(USoundBase* Song);

	void SetIsAudioPaused(bool IsAudioPaused);

	void SetProductionSelectionFactory(UFactoryBuilding* Factory);

	UFactoryBuilding* GetSelectedFactory() const;
	
	void SelectWar(UWar* War);
	void SelectCountry(UCountry* Country);
	void SelectProvince(UProvince* Province);

	UWar* GetSelectedWar();
	UCountry* GetSelectedCountry();
	UProvince* GetSelectedProvince();
	
	FOnCountryToBeInvitedToAllianceStatusChanged OnCountryToBeInvitedToAllianceStatusChanged;
private:
	UPROPERTY() UCountry* RuledCountry;
	
	UPROPERTY() UCountry* SelectedCountry; // Used for UI stuff :) TODO: Move it :)
	UPROPERTY() UProvince* SelectedProvince;
	UPROPERTY() UWar* SelectedWar;
	
	UPROPERTY() UUnitDescription* SelectedUnitDescription;
	UPROPERTY() UBuildingDescription* SelectedBuildingDescription;
	ICommandable* SelectedCommandable;

	UPROPERTY() UFactoryBuilding* SelectedFactory;

	UPROPERTY() TArray<UCountry*> ToBeInvitedCountry;

	void PawnStateChanged(TSharedPtr<FPawnState> NewPawnState);

	void PauseChanged(bool InbIsPaused);
};
