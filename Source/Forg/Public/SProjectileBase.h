// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

// Not #included in order to save on compile times. 
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USoundBase;

UCLASS(Abstract)
class FORG_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void PostInitializeComponents() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* MovementComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* ImpactSFX;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

};


