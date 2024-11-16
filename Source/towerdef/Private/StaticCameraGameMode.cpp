#include "StaticCameraGameMode.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AStaticCameraGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Find the first CameraActor in the level
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	
	if (FoundActors.Num() > 0)
	{
		// Assume the first CameraActor is the one we want to use
		ACameraActor* DefaultCamera = Cast<ACameraActor>(FoundActors[0]);
		UE_LOG(LogTemp, Warning, TEXT("Camera Component Forward Vector: %s"), *DefaultCamera->GetCameraComponent()->GetForwardVector().ToString());


		if (DefaultCamera)
		{
			// Get the player controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

			if (PlayerController)
			{
				// Set the view target to the default camera
				PlayerController->SetViewTarget(DefaultCamera);
			}
		}
	}
}