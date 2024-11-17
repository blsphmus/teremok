#include "GameController.h"

AGameController::AGameController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameController::BeginPlay()
{
	Super::BeginPlay();

	//give welcome
	//wait for 10 sec


	//init shop
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Wait for next round"));
	GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
	
}


void AGameController::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Remaining enemies: %d, Reem buffer %d"), Spawner->RemainingEnemies, PreviousRemainingEnemies);

	UE_LOG(LogTemp, Warning, TEXT("Player gold: %d"), PlayerGold);
	Super::Tick(DeltaTime);
	
	if (Spawner->RemainingEnemies == 0 and GameInit)
	{
		switch (RoundCounter)
		{
		case 0:
			
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			//
			break;

		case 1:
			PlayerGold += 200;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 2:
			PlayerGold += 300;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 3:
			PlayerGold += 500;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 4:
			PlayerGold += 1100;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 5:
			PlayerGold += 2200;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 6:
			PlayerGold += 3200;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::NextRound, 10.f, false);
			GameInit = false;
			break;
		case 7:
			PlayerGold += 5200;
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Wait for next round"));
			GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &AGameController::Bossfight, 10.f, false);
			GameInit = false;
			break;
			
		}
	}

}

void AGameController::Bossfight()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Get ready, round starts"));
	if (Spawner)
	{
		Spawner->SpawnWave(RoundCounter);
		GameInit = true;
		RoundCounter++;
	}
}

void AGameController::NextRound()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Get ready, round starts"));
	if (Spawner)
	{
		Spawner->SpawnWave(RoundCounter);
		GameInit = true;
		RoundCounter++;
	}
}


void AGameController::BuyEvo()
{
	if (Tower_frame)
	{
		if (PlayerGold - RoundCounter*100 >= 0)
		{
			PlayerGold -= RoundCounter*100;
			Tower_frame->Evo();
		}
	}
}



void AGameController::BuyTower1()
{
	if (Tower_frame)
	{
		if (PlayerGold - 50 >= 0)
		{
			if (Tower_frame->SetTowerToSlot(0))
			{
				PlayerGold -= 50;
			}
		}
	}
}


void AGameController::BuyTower2()
{
	if (Tower_frame)
	{
		if (PlayerGold - 100 >= 0)
		{
			if (Tower_frame->SetTowerToSlot(1))
			{
				PlayerGold -= 100;
			}
		}
	}
}


void AGameController::BuyTower3()
{
	if (Tower_frame)
	{
		if (PlayerGold - 250 >= 0)
		{
			if (Tower_frame->SetTowerToSlot(2))
			{
				PlayerGold -= 250;
			}
		}
	}
}