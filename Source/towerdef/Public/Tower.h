#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseEnemy.h"

#include "Tower.generated.h"

UCLASS()
class TOWERDEF_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;
	
	float AttackDamage{10.f};
	float AttackSpeed{0.5f}; //pulse interval
	float AttackRange{1000}; //detect radius

	FTimerHandle AttackPulseTimerHandle;
	void DetectAndAttack();
	ABaseEnemy* Target = nullptr;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

};
