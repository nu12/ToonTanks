// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATankGameModeBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	float GetRemainingHealthPercent() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.f;

	float Health = 0.f;
	
	ATankGameModeBase* GameMode = nullptr;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
