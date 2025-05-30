#include "tower_frame.h"

Atower_frame::Atower_frame()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);
	SpriteComponents.SetNum(24);

	for (int32 i = 0; i < 24; ++i)
	{
		FString ComponentName = FString::Printf(TEXT("SpriteComponent%d"), i);
		SpriteComponents[i] = CreateDefaultSubobject<UPaperSpriteComponent>(*ComponentName);
		SpriteComponents[i]->SetupAttachment(RootComponent);

		SpriteComponents[i]->SetVisibility(false);
		SpriteComponents[i]->SetHiddenInGame(true);

	}

	SpriteComponents[0]->SetVisibility(true);
	SpriteComponents[0]->SetHiddenInGame(false);

}


void Atower_frame::BeginPlay()
{
	Super::BeginPlay();
	FRotator CameraFacingRotation(0.0f, 0.0f, -90.0f);

	for (int32 i = 0; i < 24; ++i)
	{
		SpriteComponents[i]->SetWorldRotation(CameraFacingRotation);
		SpriteComponents[i]->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

}


void Atower_frame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Atower_frame::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0) {
		Destroy();
	}
}


void Atower_frame::Evo()
{
	Evo_counter++;

	switch (Evo_counter)
	{
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("1"));

		SpriteComponents[0]->SetVisibility(false);
		SpriteComponents[0]->SetHiddenInGame(true);

		SpriteComponents[1]->SetVisibility(true);
		SpriteComponents[1]->SetHiddenInGame(false);
		
		SpriteComponents[2]->SetVisibility(true);
		SpriteComponents[2]->SetHiddenInGame(false);
		SpriteComponents[2]->SetRelativeLocation(FVector(SpriteComponents[2]->GetRelativeLocation().X,
					SpriteComponents[2]->GetRelativeLocation().Y-907.f, SpriteComponents[2]->GetRelativeLocation().Z));
		break;

	case 2:
		UE_LOG(LogTemp, Warning, TEXT("2"));
		SpriteComponents[1]->SetVisibility(false);
		SpriteComponents[1]->SetHiddenInGame(true);
		
		SpriteComponents[3]->SetVisibility(true);
		SpriteComponents[3]->SetHiddenInGame(false);

		SpriteComponents[4]->SetVisibility(true);
		SpriteComponents[4]->SetHiddenInGame(false);
		SpriteComponents[4]->SetRelativeLocation(FVector(SpriteComponents[4]->GetRelativeLocation().X+550.f,
					SpriteComponents[4]->GetRelativeLocation().Y, SpriteComponents[4]->GetRelativeLocation().Z));

		break;

	case 3:
		UE_LOG(LogTemp, Warning, TEXT("3"));
		SpriteComponents[3]->SetVisibility(false);
		SpriteComponents[3]->SetHiddenInGame(true);
		
		SpriteComponents[4]->SetVisibility(false);
		SpriteComponents[4]->SetHiddenInGame(true);
		
		SpriteComponents[2]->SetVisibility(false);
		SpriteComponents[2]->SetHiddenInGame(true);
		
		SpriteComponents[5]->SetVisibility(true);
		SpriteComponents[5]->SetHiddenInGame(false);
		SpriteComponents[5]->SetRelativeLocation(FVector(SpriteComponents[5]->GetRelativeLocation().X+550.f,
					SpriteComponents[5]->GetRelativeLocation().Y, SpriteComponents[5]->GetRelativeLocation().Z));

		
		SpriteComponents[6]->SetVisibility(true);
		SpriteComponents[6]->SetHiddenInGame(false);
		SpriteComponents[6]->SetRelativeLocation(FVector(SpriteComponents[6]->GetRelativeLocation().X,
					SpriteComponents[6]->GetRelativeLocation().Y-907.f, SpriteComponents[6]->GetRelativeLocation().Z));
		
		SpriteComponents[7]->SetVisibility(true);
		SpriteComponents[7]->SetHiddenInGame(false);
		
		SpriteComponents[8]->SetVisibility(true);
		SpriteComponents[8]->SetHiddenInGame(false);
		SpriteComponents[8]->SetRelativeLocation(FVector(SpriteComponents[8]->GetRelativeLocation().X+550.f,
					SpriteComponents[8]->GetRelativeLocation().Y-907.f, SpriteComponents[8]->GetRelativeLocation().Z));
		break;

	case 4:
		UE_LOG(LogTemp, Warning, TEXT("4"));

		SpriteComponents[7]->SetVisibility(false);
		SpriteComponents[7]->SetHiddenInGame(true);
		
		SpriteComponents[9]->SetVisibility(true);
		SpriteComponents[9]->SetHiddenInGame(false);
		SpriteComponents[9]->SetRelativeLocation(FVector(SpriteComponents[9]->GetRelativeLocation().X-549.f,
					SpriteComponents[9]->GetRelativeLocation().Y+1, SpriteComponents[9]->GetRelativeLocation().Z));
		
		SpriteComponents[10]->SetVisibility(true);
		SpriteComponents[10]->SetHiddenInGame(false);
		break;

	case 5:
		UE_LOG(LogTemp, Warning, TEXT("5"));
		SpriteComponents[9]->SetVisibility(false);
		SpriteComponents[9]->SetHiddenInGame(true);

		SpriteComponents[6]->SetVisibility(false);
		SpriteComponents[6]->SetHiddenInGame(true);

		SpriteComponents[11]->SetVisibility(true);
		SpriteComponents[11]->SetHiddenInGame(false);
		
		SpriteComponents[10]->SetVisibility(true);
		SpriteComponents[10]->SetHiddenInGame(false);
		
		SpriteComponents[12]->SetVisibility(true);
		SpriteComponents[12]->SetHiddenInGame(false);
		SpriteComponents[12]->SetRelativeLocation(FVector(SpriteComponents[12]->GetRelativeLocation().X,
					SpriteComponents[12]->GetRelativeLocation().Y-908.f, SpriteComponents[12]->GetRelativeLocation().Z));
		
		SpriteComponents[13]->SetVisibility(true);
		SpriteComponents[13]->SetHiddenInGame(false);
		SpriteComponents[13]->SetRelativeLocation(FVector(SpriteComponents[13]->GetRelativeLocation().X-549.f,
					SpriteComponents[13]->GetRelativeLocation().Y, SpriteComponents[13]->GetRelativeLocation().Z));
		
		SpriteComponents[14]->SetVisibility(true);
		SpriteComponents[14]->SetHiddenInGame(false);
		SpriteComponents[14]->SetRelativeLocation(FVector(SpriteComponents[14]->GetRelativeLocation().X-549.f,
					SpriteComponents[14]->GetRelativeLocation().Y-908.f, SpriteComponents[14]->GetRelativeLocation().Z));
		break;
	default:
		break;
	}
}
