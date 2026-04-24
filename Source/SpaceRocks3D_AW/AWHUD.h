// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AWHUD.generated.h"

class UAWUserWidget;



/**
 * 
 */
UCLASS()
class SPACEROCKS3D_AW_API AAWHUD : public AHUD
{
	GENERATED_BODY()




public:
	// This holds a reference to the widget Blueprint class we’ll assign this in the Unreal editor
	// It only accepts classes derived from UUserWidget, so we can select our PlayerOverlay in the editor
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> PlayerOverlayClass;

	// This will hold the instance of the actual widget we create at runtime, this is what we will 
	// Show on the screen 
	TObjectPtr<UAWUserWidget> PlayerOverlay;



	//Once the object is initialized this is called - useful for wiring up the collision response
	virtual void PostInitializeComponents() override;

};
