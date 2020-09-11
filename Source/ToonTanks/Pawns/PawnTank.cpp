// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ToonTanks/Components/TankMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APawnTank::APawnTank()
{
	CreateDefaultSubobjects();
	SetupAttachments();
}

void APawnTank::CreateDefaultSubobjects()
{
	SpringArmPomponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("Movement"));
	ReloadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Reload Widget"));
}

void APawnTank::SetupAttachments()
{
	SpringArmPomponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmPomponent);
	ReloadWidgetComponent->SetupAttachment(RootComponent);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasNullPointers()) return;

	RotateTurret(GetCursorPositionInTheWorld().ImpactPoint);
	RotateWidgetTowardsPlayerCamera(ReloadWidgetComponent);
}

FHitResult APawnTank::GetCursorPositionInTheWorld()
{
	FHitResult CursosHitResult; //Out
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursosHitResult);
	return CursosHitResult;
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &APawnTank::CalculateRotationInput);
	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::Fire()
{
	if (HasNullPointers()) return;
	if (GetWorld()->GetTimeSeconds() < NextShotReadyAt) return;
	NextShotReadyAt = GetWorld()->GetTimeSeconds() + FireRate;
	Super::Fire();
}

float APawnTank::GetReloadBarValue() const
{
	return FMath::Clamp<float>(1 - ( (NextShotReadyAt - GetWorld()->GetTimeSeconds()) / FireRate), 0.f, 1.f);
}

void APawnTank::CalculateMoveInput(float Value)
{
	FVector MoveDirection = FVector(
		/* X */ Value * MovementComponent->GetMoveSpeed() * GetWorld()->DeltaTimeSeconds,
		/* Y */ 0,
		/* Z */ 0
	);
	MovementComponent->Move(MoveDirection);
}

void APawnTank::CalculateRotationInput(float Value)
{
	FRotator RotationAmount = FRotator(
		/* Pitch: Y */ 0,
		/*  Yaw:  Z */ Value * MovementComponent->GetRotationSpeed() * GetWorld()->DeltaTimeSeconds,
		/*  Roll: X */ 0
	);
	MovementComponent->Rotate(FQuat(RotationAmount));
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	
	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);	// Hide mesh
	SetActorTickEnabled(false); // Stop moving
}

bool APawnTank::IsPlayerAlive() const
{
	return bIsPlayerAlive;
}

bool APawnTank::HasNullPointers()
{
	if (Super::HasNullPointers()) return true;
	if (!PlayerController) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not found!"));
		return true;
	}
	return false;
}