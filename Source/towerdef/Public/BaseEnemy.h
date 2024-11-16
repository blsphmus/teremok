#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "tower_frame.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "TimerManager.h"
#include "DrawDebugHelpers.h" 
#include "PaperSpriteComponent.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TOWERDEF_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;
	ACameraActor* TargetCamera;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health{500};
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);
	//void FindAndRotateToCamera();

	float Damage{5};
		
	FTimerHandle DetectPulseTimerHandle;
	float DetectSphereRadius = 1000.0f;
	float DetectPulseInterval = 0.2f;
	void DetectPulse();

	void AttackPulse();
	float AttackSpeed{1};
	float AttackRange{200};
	FTimerHandle AttackPulseTimerHandle;
	FTimerHandle AttackCooldownTimerHandle;

	void MoveTowardsTarget(float DeltaTime);
	float StoppingDistance = 50.0f;
	Atower_frame* Target = nullptr;
};
