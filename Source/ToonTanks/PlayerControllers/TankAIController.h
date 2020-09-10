// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class APawn;
class APawnEnemyTank;
class UTankMovementComponent;
UCLASS()
class TOONTANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void Tick(float Delta) override;
	void SetPawn(APawn* InPawn) override;

private:
	APawnEnemyTank* ControlledPawn = nullptr;
	UTankMovementComponent* MovementComponent = nullptr;
	APawn* PlayerTank = nullptr;
};
