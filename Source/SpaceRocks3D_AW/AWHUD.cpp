// Fill out your copyright notice in the Description page of Project Settings.


#include "AWHUD.h"

#include "AWUserWidget.h"
#include "Blueprint\UserWidget.h"


void AAWHUD::PostInitializeComponents()
{

	// Always call the base class's PostInitializeComponents to ensure any parent logic runs.
	Super::PostInitializeComponents();

	// Get the generic player controller that owns this HUD (needed to create the widget properly)
	// Note: This doesn't need to be your specific player controller type
	APlayerController* PlayerController = GetOwningPlayerController();

	// Make sure we have both a valid player controller and a valid widget class before trying to create the widget
	if (PlayerController && PlayerOverlayClass)
	{
		// Create the widget using our custom UserWidget class and the specified Blueprint widget class
		PlayerOverlay = CreateWidget<UAWUserWidget>(PlayerController, PlayerOverlayClass);

		// Add the widget to the screen so the player can see it
		PlayerOverlay->AddToViewport();
	}


}
