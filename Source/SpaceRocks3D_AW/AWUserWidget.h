// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:

	void UpdateHealthBar(float Health, float MaxHealth);


};
