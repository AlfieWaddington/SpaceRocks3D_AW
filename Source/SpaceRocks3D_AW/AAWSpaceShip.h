// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class AAAWProjectile;


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

	//For angling ship during turns
	float CurrentRoll = 0;
	float CurrentPitch = 0;

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
	void OnFirePressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sphere component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	//Camera Component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	//Camera boom
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	//Static mesh
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> TheShip;

	//Name of socket for left gun
	UPROPERTY(VisibleAnywhere, Category="Combat")
	FName LeftGunSocketName = "GunLeft";

	//Name of socket for right gun
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	FName RightGunSocketName = "GunRight";

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

	//The Max Roll Angle: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Roll")
	float MaxRollAngle = 40.0f;

	//How fast ship rolls when turning: 
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Roll")
	float RollSpeed = 1.5f;

	//Max ship pitch angle:
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Roll")
	float MaxPitchAngle = 40.0f;
	
	//How fast ship pitches when ascending/descending
	//We've made this editable from within the Unreal Editor
	//In the Editor you will find these in the details panel under a "Movement" category
	UPROPERTY(EditAnywhere, Category = "Roll")
	float PitchSpeed = 1.5f;
		
	//The class to use to spawn a projectile
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AAAWProjectile> ProjectileClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Setter for enabling/disabling the input controls
	void SetInputEnabled(bool bIsEnabled);

	void printSpeed();

};
