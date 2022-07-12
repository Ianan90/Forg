// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class UWorld;
class USActionComponent;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:
	// Struct data IS replicated by default
	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
};

/**
 * 
 */
UCLASS(Blueprintable)
class FORG_API USAction : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(USActionComponent* NewActionComp);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart;
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StopAction(AActor* Instigator);
	
	// Action nickname to start/stop without a hard reference to the object
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;
	
	UWorld* GetWorld() const override;
	
	bool IsSupportedForNetworking() const override
	{
		return true;
	}

	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* ActionIcon;
	
	UPROPERTY(Replicated)
	USActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable, Category = "Action")
	USActionComponent* GetOwningComponent() const;
	
	// These NEED to be #included because it is a struct, compiler needs to know size of the struct etc.
	// When it's a pointer, forward declaring the class is not an issue as the size is already known. 
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData;
	// bool bIsRunning;

	UPROPERTY(Replicated)
	float TimeStarted;
	
	UFUNCTION()
	void OnRep_RepData();

};
