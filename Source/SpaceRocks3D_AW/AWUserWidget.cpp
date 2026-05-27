// Fill out your copyright notice in the Description page of Project Settings.


#include "AWUserWidget.h"
#include "Components\ProgressBar.h"
#include "Components\TextBlock.h"
#include "Components/Image.h"

void UAWUserWidget::UpdateHealthBar(float Health, float MaxHealth)
{
	// If the widgets exist, update them with the current health values
	if (HealthBar && HealthText)
	{
		HealthBar->SetPercent(Health / MaxHealth); // Update the progress bar

		// Create an FString from the Health and MaxHealth formatted like "75/100"
		FString HealthString = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		HealthText->SetText(FText::FromString(HealthString));  // Update the progress bar
	}
}

void UAWUserWidget::UpdateLivesDisplay(float NumLives)
{

	// ToDo 1: Safety check: Make sure the container for displaying lives is valid [DONE]
	// If it isn't then return
	if (LivesContainer) {

			// Clear any existing life icons from the UI before adding new ones
			LivesContainer->ClearChildren();

			// Loop for each remaining life and add a new icon to the container
			//ToDo 2: Loop for each remaining life
			for (int i = 0; i < NumLives; i++)
			{
				// Create a new Image widget dynamically
				UImage* LifeIcon = NewObject<UImage>(this);

				// Set the visual appearance of the icon using the LifeIconBrush.
				// We make sure this brush is assigned in the Widget Blueprint (WBP_PlayerOverlay) with an if()
				// If it isn't nothing will be shown
				if (LifeIcon)
				{
					LifeIcon->SetBrush(LifeIconBrush);
				}//Endif

				// Add the new image widget to our UI Horizontal Box container
				LivesContainer->AddChild(LifeIcon);

			}//EndFor

	}//EndIf
	else {
		return;
	}//EndElse

}//UpdateLivesDisplay


void UAWUserWidget::UpdateSpeedometer(float Speed, float MaxSpeed)
{

	// If the widgets exist, update them with the current health values
	if (Speedometer)
	{
		Speedometer->SetPercent(Speed / MaxSpeed); // Update the progress bar
	}

}//UpdateSpeedometer


void UAWUserWidget::UpdateScoreDisplay(int points)
{

	FString toDisplay = FString::FromInt(points);
	FString ScoreOut = FString(TEXT("Score: "));
	FString out = ScoreOut + toDisplay;

	if (Score)
	{
		Score->SetText(FText::FromString(out));
	}


}//UpdateScoreDisplay


