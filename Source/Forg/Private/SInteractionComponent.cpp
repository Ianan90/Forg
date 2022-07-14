// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVArDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Display Debug lines for Interaction Component."), ECVF_Cheat);


USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;

	InteractTraceDistance = 500.0f;
	InteractionRadius = 30.0f;

	CollisionChannel = ECC_WorldDynamic;
}

void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

void USInteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVArDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * InteractTraceDistance);
	
	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Clear Ref before trying to fill
	FocusedActor = nullptr;
	
	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, InteractionRadius, 32, LineColor, false, 3.0f);
		}
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	
	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 3.0f, 0, 1.0f);
	}
}

void USInteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusedActor);
}

void USInteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{
	if (InFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No focused actor to interact");
		return;
	}
	
	APawn* MyPawn = Cast<APawn>(GetOwner());
	ISGameplayInterface::Execute_Interact(InFocus, MyPawn);
}
