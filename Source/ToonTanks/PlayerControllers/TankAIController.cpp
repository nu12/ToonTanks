// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnEnemyTank.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FTimerHandle StartMovementTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StartMovementTimerHandle, this, &ATankAIController::EnableMovement, GameMode->GetStartDelay(), true);
}

void ATankAIController::Tick(float Delta)
{
	Super::Tick(Delta);
	if (!bCanMove) return;
	if (!PawnTank || !PlayerTank || !PlayerTank->IsPlayerAlive()) return;
	
	MoveToActor(PlayerTank, PawnTank->GetAcceptanceRadius());
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	PawnTank = Cast<APawnEnemyTank>(InPawn);
}

void ATankAIController::EnableMovement()
{
	bCanMove = true;
}