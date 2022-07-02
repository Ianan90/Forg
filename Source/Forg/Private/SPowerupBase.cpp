// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupBase.h"

#include "Components/SphereComponent.h"

void ASPowerupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	if (bIsActive)
	{
		DeactivatePickup();
	}
}

// Sets default values
ASPowerupBase::ASPowerupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);

	// Initialize Defaults
	bIsActive = true;
	ReactivationTime = 10.0f;
}

// Called when the game starts or when spawned
void ASPowerupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPowerupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	SetActorEnableCollision(ActiveState);
	RootComponent->SetVisibility(ActiveState, true);
}
