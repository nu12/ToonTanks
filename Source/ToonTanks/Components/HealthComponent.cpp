// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode not found!"));
		return;
	}

	if (Health <= 0) return;

	Health = FMath::Clamp<float>(Health - Damage, 0.f, DefaultHealth);

	if (Health <= 0) {
		GameMode->ActorDied(GetOwner());
	}
}
