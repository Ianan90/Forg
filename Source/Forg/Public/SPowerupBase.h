// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerupBase.generated.h"

class USphereComponent;

UCLASS()
class FORG_API ASPowerupBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupBase();
	
	void Interact_Implementation(APawn* InstigatorPawn);

	FText GetInteractionText_Implementation(APawn* InstigatorPawn);

protected:


	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
	
	FTimerHandle TimerHandle_ReactivationHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ReactivationTime;

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();
	
	void DeactivatePickup();
	
	void ActivatePickup();

	void SetActiveState(bool ActiveState);
};
