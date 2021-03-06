// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionEffect.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class FORG_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<USActionEffect> HitEffect;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTag ParryTag;
};
