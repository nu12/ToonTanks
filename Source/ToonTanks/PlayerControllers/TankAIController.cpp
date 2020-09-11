// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnEnemyTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float Delta)
{
	Super::Tick(Delta);
	if (!PawnTank || !PlayerTank || !PlayerTank->IsPlayerAlive()) return;
	
	MoveToActor(PlayerTank, PawnTank->GetAcceptanceRadius());
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	PawnTank = Cast<APawnEnemyTank>(InPawn);
}