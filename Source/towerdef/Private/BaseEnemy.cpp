#include "BaseEnemy.h"

#include "AIController.h"
#include "Spawner.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    SpriteComponents.SetNum(5);
    
    for (int i = 0; i < 5; i++) {
        FString ComponentName = FString::Printf(TEXT("SpriteComponent%d"), i);
        SpriteComponents[i] = CreateDefaultSubobject<UPaperSpriteComponent>(*ComponentName);
        
        if (SpriteComponents[i]) {
            SpriteComponents[i]->SetupAttachment(RootComponent);
            SpriteComponents[i]->SetUsingAbsoluteScale(true);
            SpriteComponents[i]->SetUsingAbsoluteRotation(true);
        }
    }
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->GravityScale = 1.0f;

    // Выбор рандомных спрайтов при создании врага
    ChooseRandomSprites();
}

void ABaseEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GetCapsuleComponent()->SetSimulatePhysics(false);

    if (Target) {
        MoveTowardsTarget(DeltaTime);
    }

    if (Health <= 0)
    {
        for (int i = 0; i < 5; i++)
        {
            SpriteComponents[i]->ConditionalBeginDestroy();
        }

        ConditionalBeginDestroy();
        this->Destroy();
    }
}

void ABaseEnemy::BeginPlay()
{
    Super::BeginPlay();
    if (SpriteComponents[0]) {
        FRotator CameraFacingRotation(0.0f, 0.0f, -90.0f);
        for (int i = 0; i < 5; i++)
        {
            SpriteComponents[i]->SetUsingAbsoluteRotation(true);
            SpriteComponents[i]->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));

            SpriteComponents[i]->SetVisibility(false);
            SpriteComponents[i]->SetHiddenInGame(true);

            SpriteComponents[i]->SetWorldRotation(CameraFacingRotation);
            SpriteComponents[i]->SetWorldRotation(CameraFacingRotation);
        }
        

        // Устанавливаем видимость для выбранных спрайтов
        for (int i = 0; i < 2; i++) {
            SpriteComponents[i]->SetVisibility(true);
            SpriteComponents[i]->SetHiddenInGame(false);
        }
        for (int i = 2; i < 4; i++) {
            SpriteComponents[i]->SetVisibility(false);
            SpriteComponents[i]->SetHiddenInGame(true);
        }
    }

    GetWorld()->GetTimerManager().SetTimer(AttackPulseTimerHandle, this, &ABaseEnemy::AttackPulse, 1.0f/AttackSpeed, true);
    GetWorld()->GetTimerManager().SetTimer(DetectPulseTimerHandle, this, &ABaseEnemy::DetectPulse, DetectPulseInterval, true);
}

void ABaseEnemy::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0)
    {
        Destroy();
    }
}

void ABaseEnemy::AttackPulse()
{
    TArray<AActor*> OverlappingActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        GetActorLocation(),
        AttackRange,
        ObjectTypes,
        Atower_frame::StaticClass(),
        TArray<AActor*>(),
        OverlappingActors
    );

    if (OverlappingActors.Num() > 0)
    {
        Target = Cast<Atower_frame>(OverlappingActors[0]);
        if (Target)
        {
            if (SpriteComponents[1])
            {
                SpriteComponents[1]->SetVisibility(true);
                SpriteComponents[1]->SetHiddenInGame(false);
                SpriteComponents[0]->SetVisibility(false);
                SpriteComponents[0]->SetHiddenInGame(true);

                GetWorld()->GetTimerManager().SetTimer(
                    AttackCooldownTimerHandle,
                    this,
                    &ABaseEnemy::ResetSpriteToDefault,
                    0.5f, 
                    false
                );
            }
        }
    }
}

void ABaseEnemy::ResetSpriteToDefault()
{
    if (SpriteComponents[0] && SpriteComponents[1])
    {
        SpriteComponents[0]->SetVisibility(true);
        SpriteComponents[0]->SetHiddenInGame(false);
        SpriteComponents[1]->SetVisibility(false);
        SpriteComponents[1]->SetHiddenInGame(true);
    }
}

void ABaseEnemy::DetectPulse()
{
    TArray<AActor*> OverlappingActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        GetActorLocation(),
        DetectSphereRadius,
        ObjectTypes,
        Atower_frame::StaticClass(),
        TArray<AActor*>(),
        OverlappingActors
    );

    if (OverlappingActors.Num() > 0)
    {
        Target = Cast<Atower_frame>(OverlappingActors[0]);
        Target->TakeDamage(Damage);
    }
}

void ABaseEnemy::MoveTowardsTarget(float DeltaTime)
{
    if (!Target)
        return;

    FVector MyLocation = GetActorLocation();
    FVector TargetLocation = Target->GetActorLocation();
    TargetLocation.Y += 400;
    float Distance = FVector::Dist(MyLocation, TargetLocation);
    FVector Direction = (TargetLocation - MyLocation).GetSafeNormal();
    AddMovementInput(Direction, 1.0f);
}

void ABaseEnemy::ChooseRandomSprites()
{
    // Рандомно выбираем, какие спрайты будут использоваться (1-2 или 3-4)
    bool bUseFirstPair = FMath::RandBool();

    if (bUseFirstPair) {
        SpriteComponents[0]->SetVisibility(true);
        SpriteComponents[0]->SetHiddenInGame(false);
        SpriteComponents[1]->SetVisibility(true);
        SpriteComponents[1]->SetHiddenInGame(false);
        SpriteComponents[2]->SetVisibility(false);
        SpriteComponents[2]->SetHiddenInGame(true);
        SpriteComponents[3]->SetVisibility(false);
        SpriteComponents[3]->SetHiddenInGame(true);
    } else {
        SpriteComponents[0]->SetVisibility(false);
        SpriteComponents[0]->SetHiddenInGame(true);
        SpriteComponents[1]->SetVisibility(false);
        SpriteComponents[1]->SetHiddenInGame(true);
        SpriteComponents[2]->SetVisibility(true);
        SpriteComponents[2]->SetHiddenInGame(false);
        SpriteComponents[3]->SetVisibility(true);
        SpriteComponents[3]->SetHiddenInGame(false);
    }
}
