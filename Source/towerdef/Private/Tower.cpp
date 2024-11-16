#include "Tower.h"


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(AttackPulseTimerHandle,
		this, &ATower::DetectAndAttack, 1.0f/AttackSpeed, true);
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATower::DetectAndAttack()
{
	DrawDebugSphere(
		GetWorld(),
		GetActorLocation(),
		AttackRange,
		32,
		FColor::Green,
		false,
		0.1f,
		0,
		1.0f
	);

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
		UE_LOG(LogTemp, Warning, TEXT("Tower find an enemy"));
		Target = Cast<ABaseEnemy>(OverlappingActors[0]);
		if (Target) Target->TakeDamage(5);
	}
}



