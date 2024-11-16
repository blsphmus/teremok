#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//#include "Tower.h"
#include "PaperSpriteComponent.h"
#include "tower_frame.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	TArray<UPaperSpriteComponent*> SpriteComponents;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	// TArray<ATower*> Towers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Frame")
	int Evo_counter{0};
	
	UFUNCTION(CallInEditor, Category = "Tower Frame")
	void Evo();
	
};
