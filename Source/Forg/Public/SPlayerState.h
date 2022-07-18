// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class ASPlayerState; // Forward declared to satisfy the delegate macros below
class USSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

class USSaveGame;

UCLASS()
class FORG_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// Get Credits
	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCredits() const;

	// Add Credits
	void AddCredits(int32 Delta);

	// Remove Credits
	bool RemoveCredits(int32 Delta);

	// Send value of object and return if can be afforded 
	bool HasEnoughCredits(int32 Delta) const;
	
	// State update for when Credits spent
	UPROPERTY(BlueprintAssignable, Category = "Credits")
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);

protected:

	UPROPERTY(EditDefaultsOnly, ReplicatedUsing="OnRep_CreditsUpdate", Category = "Credits")
	int32 Credits;

	UFUNCTION()
	void OnRep_CreditsUpdate(int32 OldCredits);
};
