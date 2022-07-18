// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPickup.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

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

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	// Check if not already at max health
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
			{
				// Only activate if healed successfully
				DeactivatePickup();
			}
		}
	}
}

FText ASPowerup_HealthPickup::GetInteractionText_Implementation(APawn* InstigatorPawn)
{
	
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health!"); 
	}
	
	ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>();
	if (PS)
	{
		if(!AttributeComp->IsFullHealth() && PS->HasEnoughCredits(CreditCost))
		return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Not enough credits!"), CreditCost); 
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum."), CreditCost);
}

#undef LOCTEXT_NAMESPACE