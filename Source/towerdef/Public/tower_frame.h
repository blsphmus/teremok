#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "tower_frame.generated.h"

class ATower;

UCLASS()
class TOWERDEF_API Atower_frame : public AActor
{
	GENERATED_BODY()
    
public:    
	Atower_frame();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health{1500};

	int TowerCount{0};
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ActivateTowerOnSlot(int SlotIndex, int TowerType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	TArray<UPaperSpriteComponent*> SpriteComponents;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	TArray<ATower*> Towers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	TArray<UPaperSpriteComponent*> TowersSprites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	TArray<UPaperSpriteComponent*> ProjectileSprites;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	int Evo_counter{0};
    
	UFUNCTION(CallInEditor, Category = "Tower Frame")
	void Evo();
	
	UFUNCTION(CallInEditor, Category = "Tower Frame")
	void EvoNull();

	UFUNCTION(CallInEditor, Category = "Tower Frame")
	bool SetTowerToSlot(int TowerType);
};