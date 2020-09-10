// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "ToonTanks/Pawns/PawnBase.h"

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<APawnBase>(GetOwner());
}

void UTankMovementComponent::Move(FVector MoveDirection)
{
	
	Owner->AddActorLocalOffset(MoveDirection, true);
	
}
void UTankMovementComponent::Rotate(FQuat RotationDirection)
{
	Owner->AddActorLocalRotation(RotationDirection, true);
}
float UTankMovementComponent::GetMoveSpeed() const
{
	return MoveSpeed;
}
float UTankMovementComponent::GetRotationSpeed() const
{
	return RotationSpeed;
}
float UTankMovementComponent::GetAcceptanceRadius() const
{
	return AcceptanceRadius;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

}
