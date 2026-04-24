// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AWPlayerController.generated.h"

class AAWHUD;

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

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void SetHUDHealth(float Health, float MaxHealth);

	



};
