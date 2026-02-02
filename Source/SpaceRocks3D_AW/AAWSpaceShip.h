// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"

#include "AAWSpaceShip.generated.h" //All includes have to go before this directive


UCLASS()
class SPACEROCKS3D_AW_API AAAWSpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAAWSpaceShip();

private:
	//These five member variables don't need to be exposed to the Unreal Editor
	FVector Velocity = FVector(0.0f, 0.0f, 0.0f);
	FVector Acceleration = FVector(0.0f, 0.0f, 0.0f);

	// Input state
	bool bCanReceiveInput = true;  //This will allow us to disable and enable the controlls, it will be useful later
	bool bIsThrusting = false;
	bool bIsBraking = false;
	int AltitudeDirection = 0;	// -1 = down, 1 = up, 0 = none
	int  TurnDirection = 0;      // -1 = left, 1 = right, 0 = none

	// Input handler method declarations
	void OnThrustPressed();
	void OnThrustReleased();
	void OnTurnLeftPressed();
	void OnTurnRightPressed();
	void OnTurnReleased();
	void OnBrakePressed();
	void OnBrakeReleased();
	void OnAscendPressed();
	void OnDescendPressed();
	void OnAltitudeReleased();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sphere component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	//Camera Component
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	//Camera boom
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	//Static mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TheShip;

	//The maximum speed: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 3500.0f;

	//The ThrustStrength will detemine the acceleration: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ThrustStrength = 800.0f;

	//The AltitudeThrustStrength will detemine the vertical acceleration: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float AltitudeThrustStrength = 600.0f;

	//The Friction: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Friction = 0.001f;

	//The Breaking Friction (higher = stronger brakes): 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float BrakingFriction = 0.003f;

	//The Rotation speed: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 30.0f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Setter for enabling/disabling the input controls
	void SetInputEnabled(bool bIsEnabled);

	void printSpeed();

};
