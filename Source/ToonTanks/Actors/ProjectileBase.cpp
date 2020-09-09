// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ParticleTrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));

	RootComponent = StaticMeshComponent;
	ParticleTrailComponent->SetupAttachment(RootComponent);

	ProjectileComponent->InitialSpeed = ProjectileSpeed;
	ProjectileComponent->MaxSpeed = ProjectileSpeed;
	InitialLifeSpan = 3.f;
}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit); // Macro for add dynamic delegate. See OnComponentHit for more information

	if (LaunchSound) UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner) return;
	if (!OtherActor || OtherActor == this || OtherActor == MyOwner) return; // Do not damage self
	if (!HitParticle) UE_LOG(LogTemp, Error, TEXT("ProjectileClass not found!"));

	if (HitSound) UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, MyOwner->GetInstigatorController(), this, DamageType);
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CameraShake);
	Destroy();
}


