// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"

class USAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, USActionComponent*, OwningComp, USAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORG_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USActionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStateStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStateStopped;

	// This NEEDS to be #included because it is a struct, compiler needs to know size of the struct etc.
	// When it's a pointer, forward declaring the class is not an issue as the size is already known. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(USAction* ActionToRemove);

	// Returns first occurrence of action matching the class provided
	UFUNCTION(BlueprintCallable, Category = "Actions")
	USAction* GetAction(TSubclassOf<USAction> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;


protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, FName ActionName);

	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, FName ActionName);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<USAction>> DefaultActions;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<USAction*> Actions;
	
};
