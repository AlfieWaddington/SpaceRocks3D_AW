// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "AWUserWidget.generated.h"

class UProgressBar;
class UTextBlock;


/**
 * 
 */
UCLASS()
class SPACEROCKS3D_AW_API UAWUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	// This variable is bound to a ProgressBar named "HealthBar" in the associated Widget Blueprint (e.g., WBP_PlayerOverlay).
	// The name here must match the name of the widget in the UMG Designer exactly.
	// The 'BindWidget' meta tag tells Unreal to automatically hook up this C++ variable to that widget at runtime.
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;    // *Must* match the widget name in the Widget Blue Print


	// This variable is bound to a TextBlock named "HealthText" in the Widget Blueprint.
	// Again, the names must match exactly, or this pointer will remain null, leading to crashes if accessed.
	// BindWidget only works when the widget is part of the widget hierarchy in the UMG Designer (i.e., not dynamically created).
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;    // *Must* match the widget name in the Widget Blue Print


	//This variable is bound to a HorizontalBox named "LivesContainer" in WBP_PlayerOverview
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LivesContainer; // *Must* match the widget name in the Widget Blue Print


	// This stores the brush (visual appearance) for the life icons displayed in the HUD.
	// A Brush defines things like the image, tint, and margin used by UMG to draw elements like UImages.
	// We store this as a value (not a pointer) because FSlateBrush is a lightweight struct,
	// not a UObject. It’s safe and typical to expose it this way to the Editor.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lives")
	FSlateBrush LifeIconBrush;

	//This variable is bound to a ProgressBar named "Speedometer" in WBP_PlayerOverview
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Speedometer;

public:

	void UpdateHealthBar(float Health, float MaxHealth);

	void UpdateLivesDisplay(float NumLives);
};
