// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORG_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	float GetHealth();

	bool IsFullHealth();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health = 100.0f;
		
};
