#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "tower_frame.h"
#include "Engine/Engine.h"
#include "GameController.generated.h"

UCLASS()
class TOWERDEF_API AGameController : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameController();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	ASpawner* Spawner{nullptr};
	FTimerHandle RoundTimerHandle;
	
	int RoundCounter;

	bool GameInit{false};

	int PlayerGold{200222};

	void NextRound();

	void Bossfight();

	UPROPERTY(EditAnywhere)
	Atower_frame* Tower_frame;

	UFUNCTION(CallInEditor, BlueprintCallable)
	void BuyEvo();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void BuyTower1();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void BuyTower2();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void BuyTower3();

	
	
};
