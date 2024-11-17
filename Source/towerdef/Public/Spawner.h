#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.h"
#include "Spawner.generated.h"

UCLASS()
class TOWERDEF_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	ASpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnEnemy();

	FTimerHandle SpawnTimerHandle;

	void SpawnWave(int RoundIndex);

	UFUNCTION(CallInEditor, Category = "Spawning")
	void Spawnsmth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 NumEnemiesToSpawn = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnRadius = 400.0f;
    
	int32 RemainingEnemies = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FRotator SpawnRotation;
    
	void SpawnOnBothSides();
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ABaseEnemy> EnemyBlueprintClass;
};