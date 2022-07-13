// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SEnemyData.generated.h"

class USAction;
/**
 * 
 */
UCLASS()
class FORG_API USEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	TSubclassOf<AActor> EnemyClass;

	// Actions/Buffs to grant this enemy usage.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	TArray<TSubclassOf<USAction>> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* EnemyIcon;

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Enemies", GetFName());
	}
	
};
