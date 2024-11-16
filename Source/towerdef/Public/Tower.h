#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseEnemy.h"
#include "PaperSpriteComponent.h"
#include "TimerManager.h"

#include "Tower.generated.h"



UCLASS()
class TOWERDEF_API ATower : public AActor
{
	GENERATED_BODY()
    
public:
	ATower();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UPaperSpriteComponent* ProjectileSpriteComponent;

	float AttackDamage{10.f};
	float AttackSpeed{3.5f}; // Pulse interval
	float AttackRange{1000.f}; // Detection radius
	float ProjectileSpeed = 5500.f; // Units per second

	FTimerHandle AttackPulseTimerHandle;
	FTimerHandle ProjectileTimerHandle;

	ABaseEnemy* Target = nullptr;

	bool bIsProjectileActive = false;

	FVector ProjectileStartLocation;
	FVector ProjectileTargetLocation;
	void RotateSpriteToFace(USceneComponent* Sprite, FVector TargetLocation);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DetectAndAttack();
	void LaunchProjectile();
	void MoveProjectile(float DeltaTime);
};
