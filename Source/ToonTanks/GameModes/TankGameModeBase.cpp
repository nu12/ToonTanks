// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetupVariables();
	HandleGameStart();
}

void ATankGameModeBase::SetupVariables()
{
	PlayerPawn = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	RemainingTurrets = GetRemainingTurretsCounter();
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ATankGameModeBase::HandleGameStart()
{
	EnablePlayerControllerWithDelay();

	GameStart(); // BlueprintImplementableEvent

	if (Music) UGameplayStatics::PlaySound2D(this, Music);
}

void ATankGameModeBase::EnablePlayerControllerWithDelay() const
{
	if (MissingPlayerController()) return;
	PlayerController->SetControllerEnabled(false); // Disable input

	FTimerHandle EnableControllerTimerHandle; // Create Time Manager and Delegate to reenable the controller
	FTimerDelegate EnableControllerDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetControllerEnabled, true);
	GetWorld()->GetTimerManager().SetTimer(EnableControllerTimerHandle, EnableControllerDelegate, StartDelay, false);
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon); // BlueprintImplementableEvent
}

void ATankGameModeBase::ActorDied(APawnBase* DeadActor)
{
	DeadActor->HandleDestruction();
	if(DeadActor == PlayerPawn)
	{
		HandleGameOver(false);
		if (!MissingPlayerController()) PlayerController->SetControllerEnabled(false); // Disable input
		return;
	}
	
	if (--RemainingTurrets <= 0) HandleGameOver(true);	
}

int32 ATankGameModeBase::GetRemainingTurretsCounter() const
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

bool ATankGameModeBase::MissingPlayerController() const
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not found!"));
		return true;
	}
	return false;
}

int32 ATankGameModeBase::GetStartDelay() const
{
	return StartDelay;
}