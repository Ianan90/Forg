// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPickup.h"

#include "SAttributeComponent.h"

ASPowerup_HealthPickup::ASPowerup_HealthPickup()
{
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	HealDelta = 20.0f;
}

void ASPowerup_HealthPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (!AttributeComp->IsFullHealth())
	{
		UE_LOG(LogTemp, Warning, TEXT("Healing!"));
		AttributeComp->ApplyHealthChange(HealDelta);
		DeactivatePickup();
	}
}
