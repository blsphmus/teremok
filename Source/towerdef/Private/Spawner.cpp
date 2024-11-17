#include "Spawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
	SpawnRotation = GetActorRotation();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy, SpawnInterval, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function to spawn an enemy
void ASpawner::SpawnEnemy()
{
	if (NumEnemiesSpawned >= NumEnemiesToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	if (!EnemyBlueprintClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyBlueprintClass is not set!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyBlueprintClass, SpawnLocation, SpawnRotation, SpawnParams);
	NewEnemy->Target = nullptr;
    NewEnemy->Health = 500;
	NewEnemy->GetCharacterMovement()->SetActive(true);
	NewEnemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	NewEnemy->GetCharacterMovement()->GravityScale = 1.f;
	NewEnemy->SpawnDefaultController();
        
	
	UE_LOG(LogTemp, Warning, TEXT("%s is moving towards the target"), *GetName());
	
	if (NewEnemy)
	{
		NumEnemiesSpawned++;
	}
}