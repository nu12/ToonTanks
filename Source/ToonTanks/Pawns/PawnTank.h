// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTankMovementComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

public:
	APawnTank();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	bool IsPlayerAlive() const;

protected:
	virtual void BeginPlay() override;

	virtual bool HasNullPointers() override;

private:
	/*======================== COMPONENTS ================================*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmPomponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTankMovementComponent* MovementComponent = nullptr;
	
	APlayerController* PlayerController = nullptr;

	/*======================== VARIABLES ================================*/
	bool bIsPlayerAlive = true;

	/*======================== FUNCTIONS ================================*/
	void CalculateMoveInput(float Value);
	void CalculateRotationInput(float Value);

	FHitResult GetCursorPositionInTheWorld();
};
