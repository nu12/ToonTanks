// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetControllerEnabled(bool ControllerEnabled)
{
	if (ControllerEnabled)
	{
		bShowMouseCursor = true;
		GetPawn()->EnableInput(this);
		return;
	}
	bShowMouseCursor = false;
	GetPawn()->DisableInput(this);		
}