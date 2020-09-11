// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UWidgetComponent;
UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	APawnBase();

	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction();

	UFUNCTION(BlueprintCallable)
	float GetHealthBarValue() const;
	
protected:
	UPROPERTY(EditAnywhere, category = "Combat")
	float FireRate = 2.f;

	void RotateTurret(FVector TargetLocation);

	virtual void Fire();

	virtual void CreateDefaultSubobjects();

	virtual void SetupAttachments();

	virtual bool HasNullPointers();

	void RotateWidgetTowardsPlayerCamera(UWidgetComponent* WidgetComponent);

private:
	/*================================ COMPONENTS ====================================*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthWidgetComponent;

	/*================================ VARIABLES ====================================*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> CameraShake;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DeathParticle = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DeathSound = nullptr;

};
