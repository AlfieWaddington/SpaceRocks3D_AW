// Fill out your copyright notice in the Description page of Project Settings.


#include "AWPlayerController.h"
#include "AWHUD.h"
#include "AWUserWidget.h"
#include "AAWSpaceShip.h"

void AAWPlayerController::BeginPlay()
{
	Super::BeginPlay();



	// ToDo: Use GetHUD() to try to get and store a reference to our custom HUD   [DONE]
	// Note: Use a cast to your custom HUD because GetHUD() returns an AHUD type  [DONE]
	TheHUD = Cast<AAWHUD>(GetHUD());
	TheShip = Cast<AAAWSpaceShip>(GetPawn());

	Lives = MaxLives;
	SetHUDLives(Lives);

}

void AAWPlayerController::Tick(float DeltaTime) 
{
	
	SetHUDSpeed(TheShip->GetSpeed(), TheShip->GetMaxSpeed());
}

void AAWPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	// ToDo: If we didn't manage to retrieve the HUD in BeginPlay() i.e it == nullptr, because of timing issues.  [DONE]
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

void AAWPlayerController::LoseLife()
{

	
	//ToDo 1: Reduce the lives by one [DONE]
	Lives--;

   //ToDo 2: Use the UE_LOG to display the number of lives [DONE]
	UE_LOG(LogTemp, Warning, TEXT("Lives = %i"), Lives);

   //ToDo 3: Fixing the instant death bug (You'll see!) [DONE]


	if (TheHUD && TheHUD->PlayerOverlay)
	{
		// ToDo 5: update the HUD's Lives, we'll do this later [DONE]
		SetHUDLives(Lives);
	}

	if (Lives <= 0)
	{
		// ToDo 6: method to handle a GameOver logic e.g. HandleGameOver(); you can do this later
		SetPause(true);
	}
	else
	{
		AAAWSpaceShip* SpaceShip = Cast<AAAWSpaceShip>(GetPawn());

		//ToDo 7: Call a method on the spaceship to Regenerate it e.g. SpaceShip->Regenerate(); we'll do this later [DONE]
		if (SpaceShip) {
			
			SpaceShip->Regenerate();
		}//if spaceship
	
	}//else

}//void LoseLife()

void AAWPlayerController::SetHUDLives(float NumLives)
{
	// ToDo: If we didn't manage to retrieve the HUD in BeginPlay() i.e it == nullptr, because of timing issues.  [DONE]
	// Try the cast again. Note: Just being safe here.
	if (TheHUD == nullptr)
	{
		TheHUD = Cast<AAWHUD>(GetHUD());
	}

	// If both the HUD and the PlayerOverlay are valid, proceed
	if (TheHUD && TheHUD->PlayerOverlay)
	{
		// Update the Health Bar on the PlayerOvelay
		TheHUD->PlayerOverlay->UpdateLivesDisplay(NumLives);
	}

}

void AAWPlayerController::SetHUDSpeed(float Speed, float MaxSpeed)
{
	// ToDo: If we didn't manage to retrieve the HUD in BeginPlay() i.e it == nullptr, because of timing issues.  [DONE]
	// Try the cast again. Note: Just being safe here.
	if (TheHUD == nullptr)
	{
		TheHUD = Cast<AAWHUD>(GetHUD());
	}

	// If both the HUD and the PlayerOverlay are valid, proceed
	if (TheHUD && TheHUD->PlayerOverlay)
	{
		// Update the Speedometer on the PlayerOvelay
		TheHUD->PlayerOverlay->UpdateSpeedometer(Speed, MaxSpeed);
	}

}

void AAWPlayerController::SetHUDScore(int Points)
{
	Score += Points;



	if (TheHUD == nullptr)
	{
		TheHUD = Cast<AAWHUD>(GetHUD());
	}

	// If both the HUD and the PlayerOverlay are valid, proceed
	if (TheHUD && TheHUD->PlayerOverlay)
	{
		// Update the Speedometer on the PlayerOvelay
		TheHUD->PlayerOverlay->UpdateScoreDisplay(Score);
	}

}

AAWPlayerController::AAWPlayerController()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

	



