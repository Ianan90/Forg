// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupBase.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerupBase::ASPowerupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// REPLICATION 
	bReplicates =  true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);

	// Initialize Defaults
	bIsActive = true;
	ReactivationTime = 10.0f;	
}

void ASPowerupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Logic implementation in derived classes
}

FText ASPowerupBase::GetInteractionText_Implementation(APawn* InstigatorPawn)
{
	return FText::GetEmpty();
}

void ASPowerupBase::DeactivatePickup()
{
	bIsActive = false;
	SetActiveState(bIsActive);
	// Timer for when power up should be active again. 
	GetWorldTimerManager().SetTimer(TimerHandle_ReactivationHandle, this, &ASPowerupBase::ActivatePickup, ReactivationTime);
}

void ASPowerupBase::ActivatePickup()
{
	bIsActive = true;
	SetActiveState(bIsActive);
}

void ASPowerupBase::SetActiveState(bool ActiveState)
{
	bIsActive = ActiveState;
	OnRep_IsActive();
}

void ASPowerupBase::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}

void ASPowerupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME - C = Class, V = Value
	DOREPLIFETIME(ASPowerupBase, bIsActive);
}