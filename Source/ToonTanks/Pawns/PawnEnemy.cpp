// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	SetTimerHandle();
}

void APawnEnemy::SetTimerHandle()
{
	FTimerHandle FireRateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnEnemy::CheckFireCondition, FireRate, true);
}

bool APawnEnemy::HasNullPointers()
{
	if (Super::HasNullPointers()) return true;
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn not found!"));
		return true;
	}
	return false;
}


void APawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasNullPointers()) return;
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnEnemy::CheckFireCondition()
{
	if (HasNullPointers()) return;

	if (!PlayerPawn->IsPlayerAlive()) return;

	if (GetDistanceToPawn() > FireRange) return;

	Fire();
}

float APawnEnemy::GetDistanceToPawn()
{
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnEnemy::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}