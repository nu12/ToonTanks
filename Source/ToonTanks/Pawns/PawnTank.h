// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTankMovementComponent;
class UWidgetComponent;

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

	UFUNCTION(BlueprintCallable)
	float GetReloadBarValue() const;

protected:
	virtual void BeginPlay() override;

	virtual void Fire() override;

	virtual bool HasNullPointers() override;


private:
	/*======================== COMPONENTS ================================*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmPomponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTankMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* ReloadWidgetComponent;
	
	APlayerController* PlayerController = nullptr;

	/*======================== VARIABLES ================================*/
	bool bIsPlayerAlive = true;

	float NextShotReadyAt = 0.f;

	/*======================== FUNCTIONS ================================*/
	void CalculateMoveInput(float Value);

	void CalculateRotationInput(float Value);

	void CreateDefaultSubobjects();

	void SetupAttachments();

	FHitResult GetCursorPositionInTheWorld();
};
