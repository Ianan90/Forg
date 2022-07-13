// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class USSaveGame;
class USEnemyData;

USTRUCT(BlueprintType)
struct FEnemyInfoRow: public  FTableRowBase
{
	GENERATED_BODY()

public:

	// Default Values
	FEnemyInfoRow()
	{
		Weight = 1.0f;
		SpawnCost = 5.0f;
		KillReward = 20.0f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId EnemyID;
	// USEnemyData* EnemyData;
	// TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	// Some cost for the game mode to request enemy spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	// Credit Reward
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward;
};
/**
 * 
 */
UCLASS()
class FORG_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASGameModeBase();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadSaveGame();

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	UFUNCTION(Exec)
	void KillAllAI();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* EnemyTable;
	
	// UPROPERTY(EditDefaultsOnly, Category = "AI")
	// TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 CreditsPerKill;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	void OnMonsterLoaded(FPrimaryAssetId PrimaryAssetId, FVector SpawnLocation);

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UPROPERTY()
	USSaveGame* CurrentSaveGame;
	
	FString SlotName;

};
