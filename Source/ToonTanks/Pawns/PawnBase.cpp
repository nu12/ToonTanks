// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));

	RootComponent = CapsuleComponent;
	BaseMesh->SetupAttachment(RootComponent);
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//HealthWidgetComponent->GetWidgetClass();
	RotateWidgetTowardsPlayerCamera();
}

void APawnBase::RotateWidgetTowardsPlayerCamera()
{
	FRotator FaceCameraRotation = UKismetMathLibrary::FindLookAtRotation(
		HealthWidgetComponent->GetComponentLocation(),									// Widget location
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation()	// Camera location

	);
	HealthWidgetComponent->SetWorldRotation(FaceCameraRotation);
}

void APawnBase::RotateTurret(FVector TargetLocation)
{
	FVector TurretLocation = GetActorLocation();
	TurretLocation.Z = TargetLocation.Z;
	FRotator RotationDirection = FVector(TargetLocation - TurretLocation).Rotation();

	TurretMesh->SetWorldRotation(RotationDirection);
}

void APawnBase::Fire()
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileClass not found!"));
		return;
	}

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this); // Prevent the projectile to damage the Pawn

}

void APawnBase::HandleDestruction()
{
	if(!DeathParticle)
	{
		UE_LOG(LogTemp, Error, TEXT("DeathParticle not found!"));
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	if (DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CameraShake);
}

float APawnBase::GetHealthBarValue() const
{
	return HealthComponent->GetRemainingHealthPercent();
}
