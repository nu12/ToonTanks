// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArmPomponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArmPomponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmPomponent);

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

	Rotate();
	Move();
	RotateTurret(GetCursorPositionInTheWorld().ImpactPoint);
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

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(
		Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,	// X axis, a.k.a Forward vector
		0,													// Y
		0													// Z
	);
}

void APawnTank::CalculateRotationInput(float Value)
{
	FRotator RotationAmount = FRotator(
		0,														//Pitch: Y
		Value * RotationSpeed * GetWorld()->DeltaTimeSeconds,	// Yaw:  Z
		0														// Roll: X
	);
	RotationDirection = FQuat(RotationAmount);
}

void APawnTank::Move() 
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate() 
{
	AddActorLocalRotation(RotationDirection, true);
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
	Super::HasNullPointers();
	if (!PlayerController) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not found!"));
		return true;
	}
	return false;
}