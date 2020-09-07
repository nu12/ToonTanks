// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

#include "DrawDebugHelpers.h"

void APawnTurret::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	DrawDebugCircle(GetWorld(), GetActorLocation(), FireRange, 100, FColor::Red, false,10.f, (uint8)'\000', 10.f, FVector(1.f, 0.f, 0.f), FVector(0.f, 1.f, 0.f));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APawnTurret::CheckFireCondition() const
{
	if (!PlayerPawn) return;

	//if (PlayerPawn.IsDead()) return;

	if (GetDistanceToPawn() > FireRange) return;

	// Fire();

	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}

float APawnTurret::GetDistanceToPawn() const
{
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}