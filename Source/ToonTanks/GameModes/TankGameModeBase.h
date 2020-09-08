// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)	// It will be called in a Blueprint class
	void GameStart();						// In this case it doesn't need C++ implementation
	UFUNCTION(BlueprintImplementableEvent)	// It will be called in a Blueprint class
	void GameOver(bool PlayerWon);			// In this case it doesn't need C++ implementation

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

};
