// Fill out your copyright notice in the Description page of Project Settings.


#include "AWUserWidget.h"
#include "Components\ProgressBar.h"
#include "Components\TextBlock.h"

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
