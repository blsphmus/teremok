#include "BaseEnemy.h"




ABaseEnemy::ABaseEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
    if (SpriteComponent) {
        SpriteComponent->SetupAttachment(RootComponent);
        SpriteComponent->SetUsingAbsoluteScale(true);
        SpriteComponent->SetUsingAbsoluteRotation(true);
        
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
        this->Destroy();
    }
}


void ABaseEnemy::BeginPlay()
{
    Super::BeginPlay();
    if (SpriteComponent) {
        SpriteComponent->SetUsingAbsoluteRotation(true);

        //FRotator CameraFacingRotation(0.0f, -0.0f, -90.0f);

        FRotator CameraFacingRotation(0.0f, 0.0f, -90.0f);
        //FRotator CameraFacingRotation(0.0f, +0.342f, +0.940f); 
        SpriteComponent->SetWorldScale3D(FVector(-0.2f, 0.2f, 0.2f));
        
        // SpriteComponent->SetWorldScale3D(FVector(-SpriteComponent->GetRelativeScale3D().X,
        //     SpriteComponent->GetRelativeScale3D().X,
        //     SpriteComponent->GetRelativeScale3D().X));   // x flip
        
        SpriteComponent->SetWorldRotation(CameraFacingRotation);
        UE_LOG(LogTemp, Warning, TEXT("SpriteComponent Initial Rotation: %s"), *SpriteComponent->GetComponentRotation().ToString());
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
    // DrawDebugSphere(
    //     GetWorld(),
    //     GetActorLocation(),
    //     AttackRange,
    //     32,
    //     FColor::Red,
    //     false,
    //     0.2f,
    //     0,
    //     3.0f
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
        UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
        Target = Cast<Atower_frame>(OverlappingActors[0]); 
        if (Target) { UE_LOG(LogTemp, Warning, TEXT("Target Tower found using : %s"), *Target->GetName()); }
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
        UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
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
