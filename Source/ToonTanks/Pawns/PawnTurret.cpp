// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

#include "DrawDebugHelpers.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	SetTimerHandle();
}

bool APawnTurret::HasNullPointers()
{
	Super::HasNullPointers();
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn not found!"));
		return true;
	}
	return false;
}

void APawnTurret::SetTimerHandle()
{
	FTimerHandle FireRateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasNullPointers()) return;
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (HasNullPointers()) return;

	if (!PlayerPawn->IsPlayerAlive()) return;

	if (GetDistanceToPawn() > FireRange) return;

	Fire();
}

float APawnTurret::GetDistanceToPawn()
{
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}