#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StaticCameraGameMode.generated.h"

UCLASS()
class TOWERDEF_API AStaticCameraGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

};
