#include "BaseEnemy.h"

#include "AIController.h"
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
        SpriteComponents[0]->SetUsingAbsoluteRotation(true);
        SpriteComponents[1]->SetUsingAbsoluteRotation(true);
        FRotator CameraFacingRotation(0.0f, 0.0f, -90.0f);
        SpriteComponents[0]->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));
        SpriteComponents[1]->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));
        

        SpriteComponents[1]->SetVisibility(false);
        SpriteComponents[1]->SetHiddenInGame(true);
        
        SpriteComponents[0]->SetWorldRotation(CameraFacingRotation);
        SpriteComponents[1]->SetWorldRotation(CameraFacingRotation);

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
        Target = Cast<Atower_frame>(OverlappingActors[0]);
        Target->TakeDamage(Damage);

        if (Target) {
            UE_LOG(LogTemp, Warning, TEXT("Target detected: %s"), *Target->GetName());
        }

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
