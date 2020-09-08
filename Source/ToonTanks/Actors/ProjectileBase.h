// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UProjectileMovementComponent* ProjectileComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileSpeed = 1300.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileDamage = 50.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
