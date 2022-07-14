// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SERVER REPLICATION
	bReplicates = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

}

void ASItemChest::OnActorLoaded_Implementation()
{
	ISGameplayInterface::OnActorLoaded_Implementation();
	OnRep_LidOpened();
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// This calls OnRep_LidOpened for CLIENTS as it's linked to a RepNotifier
	bLidOpened = !bLidOpened;
	
	// Manually Called for the SERVER
	OnRep_LidOpened();
}

void ASItemChest::OnRep_LidOpened()
{
	float CurvePitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurvePitch, 0, 0));
}

void ASItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME - C = Class, V = Value
	DOREPLIFETIME(ASItemChest, bLidOpened);
}