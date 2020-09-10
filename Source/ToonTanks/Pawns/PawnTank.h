// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

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
	
	APlayerController* PlayerController = nullptr;

	/*======================== VARIABLES ================================*/
	// Tank movement
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 200.f;

	bool bIsPlayerAlive = true;

	FVector MoveDirection;
	FQuat RotationDirection;

	/*======================== FUNCTIONS ================================*/
	void CalculateMoveInput(float Value);
	void CalculateRotationInput(float Value);

	void Move();
	void Rotate();

	FHitResult GetCursorPositionInTheWorld();
};
