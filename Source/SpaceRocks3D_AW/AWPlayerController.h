// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AWPlayerController.generated.h"

class AAWHUD;
class AAAWSpaceShip;

/**
 * 
 */
UCLASS()
class SPACEROCKS3D_AW_API AAWPlayerController : public APlayerController
{
	GENERATED_BODY()
	


private:

	// This will hold the instance of the custom HUD we've written
	AAWHUD* TheHUD;
	AAAWSpaceShip* TheShip;


	int Lives = 0;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int MaxLives = 3;

	int Score = 0;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHUDHealth(float Health, float MaxHealth);

	void LoseLife();

	void SetHUDLives(float Lives);

	void SetHUDSpeed(float Speed, float MaxSpeed);

	AAWPlayerController();
};
