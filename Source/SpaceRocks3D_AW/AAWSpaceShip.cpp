// Fill out your copyright notice in the Description page of Project Settings.


#include "AAWSpaceShip.h"

// Sets default values
AAAWSpaceShip::AAAWSpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a USphereComponent to act as a proximity sensor and make it the Root Component,
    // this gives us a clean transform we can build other components around (like the mesh and camera).
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("A Sphere Component"));      
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(1500.0f);

	// Create the USpringArmComponent and attach it to the root component,
	// this means that its transform is relative to the root component 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("The Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800;
	SpringArm->SetRelativeLocation(FVector(-800, 0, 300));

	// Create the UCameraComponent and attach it to the spring arm,
	// this means that its transform is relative to the spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("The Camera"));
	Camera->SetupAttachment(SpringArm);

	// Create the UStaticMeshComponent and attach it to the USphere component,
	// this means that its transform is relative to the spring arm
	TheShip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Mesh"));
	TheShip->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AAAWSpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAWSpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAAWSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);

}

