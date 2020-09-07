// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, category = "Combat")
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, category = "Combat")
	float FireRange = 500.f;
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition() const;
	float GetDistanceToPawn() const;

	APawnTank* PlayerPawn = nullptr;

};
