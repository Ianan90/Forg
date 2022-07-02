// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupBase.h"
#include "SPowerup_HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class FORG_API ASPowerup_HealthPickup : public ASPowerupBase
{
	GENERATED_BODY()

protected:
	ASPowerup_HealthPickup();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float HealDelta;
};
