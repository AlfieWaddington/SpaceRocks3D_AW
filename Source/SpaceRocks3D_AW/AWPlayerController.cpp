// Fill out your copyright notice in the Description page of Project Settings.


#include "AWPlayerController.h"
#include "AWHUD.h"
#include "AWUserWidget.h"

void AAWPlayerController::BeginPlay()
{
	Super::BeginPlay();


	TheHUD = Cast<AAWHUD>(GetHUD());
	

	// ToDo: Use GetHUD() to try to get and store a reference to our custom HUD
	// Note: Use a cast to your custom HUD because GetHUD() returns an AHUD type
}

void AAWPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	// ToDo: If we didn't manage to retrieve the HUD in BeginPlay() i.e it == nullptr, because of timing issues. 
	// Try the cast again. Note: Just being safe here.
	if (TheHUD == nullptr)
		{
			TheHUD = Cast<AAWHUD>(GetHUD());
		}

		// If both the HUD and the PlayerOverlay are valid, proceed
		if (TheHUD && TheHUD->PlayerOverlay)
		{
			// Update the Health Bar on the PlayerOvelay
			TheHUD->PlayerOverlay->UpdateHealthBar(Health, MaxHealth);
		}
}