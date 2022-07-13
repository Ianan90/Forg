// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPickup.h"

#include "SAttributeComponent.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASPowerup_HealthPickup::ASPowerup_HealthPickup()
{
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CreditCost = 50;
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
		AttributeComp->ApplyHealthChange(this, HealDelta);
		DeactivatePickup();
	}
}

FText ASPowerup_HealthPickup::GetInteractionText_Implementation(AActor* InstigatorPawn)
{
	
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health!"); 
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to full"), CreditCost); 
 
}

#undef LOCTEXT_NAMESPACE