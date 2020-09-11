// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnEnemy.generated.h"

class APawnTank;
UCLASS()
class TOONTANKS_API APawnEnemy : public APawnBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

	virtual bool HasNullPointers() override;

private:
	APawnTank* PlayerPawn = nullptr;

	UPROPERTY(EditAnywhere, category = "Combat")
	float FireRange = 500.f;

	void SetTimerHandle();

	void CheckFireCondition();

	float GetDistanceToPawn();
};
