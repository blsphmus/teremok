#include "BaseEnemy.h"

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
}


void ABaseEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Target) {
        MoveTowardsTarget(DeltaTime);
    }

    if (Health <= 0)
    {
        // Уничтожаем все компоненты перед уничтожением объекта
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
        SpriteComponents[0]->SetUsingAbsoluteRotation(true);
        SpriteComponents[1]->SetUsingAbsoluteRotation(true);
        FRotator CameraFacingRotation(0.0f, 0.0f, -90.0f);
        SpriteComponents[0]->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));
        SpriteComponents[1]->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));

        SpriteComponents[1]->SetVisibility(false);
        SpriteComponents[1]->SetHiddenInGame(true);
        
        // SpriteComponent->SetWorldScale3D(FVector(-SpriteComponent->GetRelativeScale3D().X,
        //     SpriteComponent->GetRelativeScale3D().X,
        //     SpriteComponent->GetRelativeScale3D().X));   // x flip
        
        SpriteComponents[0]->SetWorldRotation(CameraFacingRotation);
        SpriteComponents[1]->SetWorldRotation(CameraFacingRotation);

        //UE_LOG(LogTemp, Warning, TEXT("SpriteComponent Initial Rotation: %s"), *SpriteComponents[0]->GetComponentRotation().ToString());
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
        //UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
        Target = Cast<Atower_frame>(OverlappingActors[0]);
        if (Target)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Target Tower found: %s"), *Target->GetName());

            // Смена на SpriteComponent[1]
            if (SpriteComponents[1])
            {
                SpriteComponents[1]->SetVisibility(true);
                SpriteComponents[1]->SetHiddenInGame(false);
                SpriteComponents[0]->SetVisibility(false);
                SpriteComponents[0]->SetHiddenInGame(true);

                // Установка таймера для возврата к SpriteComponent[0]
                GetWorld()->GetTimerManager().SetTimer(
                    AttackCooldownTimerHandle,
                    this,
                    &ABaseEnemy::ResetSpriteToDefault,
                    0.5f, // Время ожидания
                    false
                );
            }
        }
    }
}

void ABaseEnemy::ResetSpriteToDefault()
{
    // Возвращение к SpriteComponent[0]
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

    // DrawDebugSphere(
    //     GetWorld(),
    //     GetActorLocation(),
    //     DetectSphereRadius,
    //     32,
    //     FColor::Blue,
    //     false,
    //     0.1f,
    //     0,
    //     1.0f
    // );

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
        //UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
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
