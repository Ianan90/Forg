// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

bool USAttributeComponent::IsFullHealth()
{
	return (Health >= MaxHealth);
}

