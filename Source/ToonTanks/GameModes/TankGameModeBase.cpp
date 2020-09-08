// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::HandleGameStart()
{
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	RemainingTurrets = GetRemainingTurretsCounter();

	GameStart(); // BlueprintImplementableEvent: Call the funciton in the Blueprint
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	if(PlayerWon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Won"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Lost"));
	}
	GameOver(PlayerWon); // BlueprintImplementableEvent: Call the funciton in the Blueprint
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if(DeadActor == PlayerPawn)
	{
		PlayerPawn->HandleDestruction();
		HandleGameOver(false);
	}
	else if(APawnTurret* DeadTurret = Cast<APawnTurret>(DeadActor))
	{
		DeadTurret->HandleDestruction();
		
		if (--RemainingTurrets <= 0) {
			HandleGameOver(true);
		}
	}
	
}

int32 ATankGameModeBase::GetRemainingTurretsCounter()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}