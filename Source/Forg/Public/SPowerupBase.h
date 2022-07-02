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
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
	
	FTimerHandle TimerHandle_ReactivationHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ReactivationTime;

	bool bIsActive;

	void DeactivatePickup();
	
	void ActivatePickup();

	void SetActiveState(bool ActiveState);
};