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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
