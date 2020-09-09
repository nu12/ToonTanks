// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::HandleGameStart()
{
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	RemainingTurrets = GetRemainingTurretsCounter();

	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	GameStart(); // BlueprintImplementableEvent: Call the funciton in the Blueprint

	if (PlayerController) 
	{
		PlayerController->SetControllerEnabled(false); // Disable input

		// Create Time Manager and Delegate to reenable the controller
		FTimerHandle EnableControllerTimerHandle;
		FTimerDelegate EnableControllerDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetControllerEnabled, true);
		GetWorld()->GetTimerManager().SetTimer(
			EnableControllerTimerHandle,
			EnableControllerDelegate,
			StartDelay,
			false
		);
	}

	if (Music) UGameplayStatics::PlaySound2D(this, Music);
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

		PlayerController->SetControllerEnabled(false); // Disable input
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