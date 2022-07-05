// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

/**
 * 
 */
UCLASS()
class FORG_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// Get Credits
	int32 GetCredits() const;

	// Add Credits
	void AddCredits(int32 Delta);

	// Remove Credits
	bool RemoveCredits(int32 Delta);
	
	// State update for when Credits spent
	UPROPERTY(BlueprintAssignable, Category = "Credits")
	FOnCreditsChanged OnCreditsChanged;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Credits")
	int32 Credits;
};
