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

    //SpawnLocation = GetActorLocation();
    //SpawnRotation = GetActorRotation();
    //GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy, SpawnInterval, true);
}

void ASpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Подсчет оставшихся врагов
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), FoundEnemies);
    RemainingEnemies = FoundEnemies.Num();

    // Лог для отладки
    //UE_LOG(LogTemp, Warning, TEXT("Remaining enemies: %d"), RemainingEnemies);
}

void ASpawner::SpawnEnemy()
{
    if (!EnemyBlueprintClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnemyBlueprintClass is not set!"));
        return;
    }

    FVector RandomSpawnLocation = SpawnLocation;
    RandomSpawnLocation.X += FMath::FRandRange(-SpawnRadius, SpawnRadius);
    RandomSpawnLocation.Y += FMath::FRandRange(-SpawnRadius, SpawnRadius);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyBlueprintClass, RandomSpawnLocation, SpawnRotation, SpawnParams);
    NewEnemy->Target = nullptr;
    NewEnemy->Health = 300;
    NewEnemy->GetCharacterMovement()->SetActive(true);
    NewEnemy->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
    NewEnemy->GetCharacterMovement()->GravityScale = 1.f;
    NewEnemy->SpawnDefaultController();
        
    UE_LOG(LogTemp, Warning, TEXT("%s is moving towards the target"), *GetName());
    
    if (NewEnemy)
    {
        RemainingEnemies++;

        // Рандомно выбираем, какие спрайты будут использоваться (1-2 или 3-4)
        bool bUseFirstPair = FMath::RandBool();

        if (bUseFirstPair) {
            NewEnemy->SpriteComponents[0]->SetVisibility(true);
            NewEnemy->SpriteComponents[0]->SetHiddenInGame(false);
            NewEnemy->SpriteComponents[1]->SetVisibility(true);
            NewEnemy->SpriteComponents[1]->SetHiddenInGame(false);
            NewEnemy->SpriteComponents[2]->SetVisibility(false);
            NewEnemy->SpriteComponents[2]->SetHiddenInGame(true);
            NewEnemy->SpriteComponents[3]->SetVisibility(false);
            NewEnemy->SpriteComponents[3]->SetHiddenInGame(true);
        } else {
            NewEnemy->SpriteComponents[0]->SetVisibility(false);
            NewEnemy->SpriteComponents[0]->SetHiddenInGame(true);
            NewEnemy->SpriteComponents[1]->SetVisibility(false);
            NewEnemy->SpriteComponents[1]->SetHiddenInGame(true);
            NewEnemy->SpriteComponents[2]->SetVisibility(true);
            NewEnemy->SpriteComponents[2]->SetHiddenInGame(false);
            NewEnemy->SpriteComponents[3]->SetVisibility(true);
            NewEnemy->SpriteComponents[3]->SetHiddenInGame(false);
        }
    }
}

void ASpawner::Spawnsmth()
{
    SpawnWave(1);
}

void ASpawner::SpawnOnBothSides()
{
    for (int i = 0; i < NumEnemiesToSpawn/2; i++)
    {
        SpawnLocation = FVector3d(1000, 2500, 50);
        SpawnEnemy();
    }

    for (int i = 0; i < NumEnemiesToSpawn/2; i++)
    {
        SpawnLocation = FVector3d(-2200, 2500, 50);
        SpawnEnemy();
    }
}

void ASpawner::SpawnWave(int RoundIndex)
{
    if (RoundIndex == 0) {
        NumEnemiesToSpawn = 6;
        SpawnOnBothSides();
    } else if (RoundIndex == 1) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    } else if (RoundIndex == 2) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    } else if (RoundIndex == 3) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    } else if (RoundIndex == 4) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    } else if (RoundIndex == 5) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    } else if (RoundIndex == 6) {
        NumEnemiesToSpawn = 10;
        SpawnOnBothSides();
    }
}