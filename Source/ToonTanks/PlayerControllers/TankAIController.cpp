// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Pawns/PawnEnemyTank.h"
#include "ToonTanks/Components/TankMovementComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::Tick(float Delta)
{
	Super::Tick(Delta);
	if (!ControlledPawn || !PlayerTank) return;
	MoveToActor(PlayerTank, 100.f);
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	ControlledPawn = Cast<APawnEnemyTank>(InPawn);
	//if (!ControlledPawn) return;
	//MovementComponent = ControlledPawn->FindComponentByClass<UTankMovementComponent>();
}