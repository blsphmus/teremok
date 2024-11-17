#include "Tower.h"
#include "DrawDebugHelpers.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TowerSprite"));
    RootComponent = SpriteComponent;

    ProjectileSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileSprite"));
    ProjectileSpriteComponent->SetupAttachment(RootComponent);
    ProjectileSpriteComponent->SetVisibility(false);

    SpriteComponent->SetRelativeScale3D(FVector3d(0.4f, 0.4f, 0.4f));
    ProjectileSpriteComponent->SetRelativeScale3D(FVector3d(0.4f, 0.4f, 0.4f));

}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    ProjectileSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetWorld()->GetTimerManager().SetTimer(
        AttackPulseTimerHandle,
        this,
        &ATower::DetectAndAttack,
        1.0f / AttackSpeed,
        true
    );
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsProjectileActive)
    {
        MoveProjectile(DeltaTime);
    }

    if (Target)
    {
        RotateSpriteToFace(SpriteComponent, Target->GetActorLocation());
    }

    
}

void ATower::DetectAndAttack()
{
    
    TArray<AActor*> OverlappingActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        GetActorLocation(),
        AttackRange,
        ObjectTypes,
        ABaseEnemy::StaticClass(),
        TArray<AActor*>(),
        OverlappingActors
    );

    if (OverlappingActors.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tower found an enemy"));
        Target = Cast<ABaseEnemy>(OverlappingActors[0]);

        if (Target && !bIsProjectileActive)
        {
            RotateSpriteToFace(SpriteComponent, Target->GetActorLocation());
            LaunchProjectile();
        }
    }
}


void ATower::LaunchProjectile()
{
    if (!Target)
        return;

    bIsProjectileActive = true;
    ProjectileSpriteComponent->SetVisibility(true);
    ProjectileStartLocation = GetActorLocation();
    ProjectileTargetLocation = Target->GetActorLocation();
    ProjectileSpriteComponent->SetWorldLocation(ProjectileStartLocation);
    RotateSpriteToFace(ProjectileSpriteComponent, ProjectileTargetLocation);
}


void ATower::MoveProjectile(float DeltaTime)
{
    if (!Target)
    {
        bIsProjectileActive = false;
        ProjectileSpriteComponent->SetVisibility(false);
        return;
    }

    FVector CurrentLocation = ProjectileSpriteComponent->GetComponentLocation();
    FVector Direction = (ProjectileTargetLocation - CurrentLocation).GetSafeNormal();
    FVector NewLocation = CurrentLocation + Direction * ProjectileSpeed * DeltaTime;

    ProjectileSpriteComponent->SetWorldLocation(NewLocation);

    if (FVector::Dist(NewLocation, ProjectileTargetLocation) < 50.f)
    {
        if (Target)
        {
            Target->TakeDamage(AttackDamage);
        }

        bIsProjectileActive = false;
        ProjectileSpriteComponent->SetVisibility(false);
    }
}

void ATower::RotateSpriteToFace(USceneComponent* Sprite, FVector TargetLocation)
{
    if (!Sprite)
        return;

    FVector Direction = (TargetLocation - Sprite->GetComponentLocation()).GetSafeNormal();
    FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

    NewRotation.Pitch = 180.0f;
    NewRotation.Roll = 90.0f;

    Sprite->SetWorldRotation(NewRotation);
}
