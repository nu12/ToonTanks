// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

#include "DrawDebugHelpers.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	DrawDebugCircle(GetWorld(), GetActorLocation(), FireRange, 100, FColor::Red, false,10.f, (uint8)'\000', 10.f, FVector(1.f, 0.f, 0.f), FVector(0.f, 1.f, 0.f));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn not found!"));
		return;
	}

	if (GetDistanceToPawn() > FireRange) return;

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn) return;

	//if (PlayerPawn.IsDead()) return;

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
	UE_LOG(LogTemp, Warning, TEXT("HandleDestruction from Turret!"));
}