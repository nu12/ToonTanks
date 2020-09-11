// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnBase;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(APawnBase* DeadActor);
	
	UFUNCTION(BlueprintCallable)
	int32 GetRemainingTurretsCounter() const;

	int32 GetStartDelay() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)	// It will be called in a Blueprint class
	void GameStart();						// In this case it doesn't need C++ implementation

	UFUNCTION(BlueprintImplementableEvent)	// It will be called in a Blueprint class
	void GameOver(bool PlayerWon);			// In this case it doesn't need C++ implementation

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	
	void SetupVariables();
	void EnablePlayerControllerWithDelay() const;
	bool MissingPlayerController() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (AllowPrivateAccess = "true"))
	int32 StartDelay = 3;

	APawnBase* PlayerPawn = nullptr;

	APlayerControllerBase* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, Category = "Music")
	USoundBase* Music = nullptr;

	int32 RemainingTurrets = 0;
};
