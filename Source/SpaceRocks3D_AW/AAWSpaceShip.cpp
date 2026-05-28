// Fill out your copyright notice in the Description page of Project Settings.


#include "AAWSpaceShip.h"

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectiles/AAWProjectile.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet\GameplayStatics.h"
#include "AWPlayerController.h"
#include "Attributes/AWAttributeComponent.h"


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
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

	// Create the USpringArmComponent and attach it to the root component,
	// this means that its transform is relative to the root component 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("The Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800;
	SpringArm->SetRelativeLocation(FVector(-600, 0, 230));
	SpringArm->AddRelativeRotation(FRotator(-7, 0, 0));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;


	// Create the UCameraComponent and attach it to the spring arm,
	// this means that its transform is relative to the spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("The Camera"));
	Camera->SetupAttachment(SpringArm);

	// Create the UStaticMeshComponent and attach it to the USphere component,
	// this means that its transform is relative to the spring arm
	TheShip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Mesh"));
	TheShip->SetupAttachment(RootComponent);
	//SetCollisionProfile for default behaviour
	TheShip->SetCollisionProfileName(TEXT("Spaceship"));
	// Enable collision notifications so we can respond to impacts (e.g., OnComponentHit events)
	TheShip->SetNotifyRigidBodyCollision(true);

	HealthAttribute = CreateDefaultSubobject<UAWAttributeComponent>(TEXT("The player's health"));
	

	EngineSound = CreateDefaultSubobject<UAudioComponent>(TEXT("The engine noise"));
	EngineSound->SetupAttachment(RootComponent);

	EngineTrail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("The engine particle effect"));
	EngineTrail->SetupAttachment(RootComponent);
	EngineTrail->Deactivate();

}

// Called when the game starts or when spawned
void AAAWSpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Health to MaxHealth 
	Health = MaxHealth;

	// Attempt to cast the generic 'PlayerController' to our custom player controller class 
	// This is needed because the Controller variable that is inherrited by the SpaceShip from the Pawn class is of type AController*, 
	// which doesn’t know about our custom methods e.g. SetHUDHealth(Health, MaxHealth)
	PlayerController = Cast<AAWPlayerController>(GetController());

	// If the cast was successful (i.e., the controller is actually an ASR3DPlayerController)
	if (PlayerController)
	{
		// Call the custom method we defined on ASR3DPlayerController to update the HUD with the player's current and max health
		PlayerController->SetHUDHealth(Health, MaxHealth);
	}

	EngineTrail->Deactivate();

}

// Called every frame
void AAAWSpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set the accelration to zero at the start of each frame
	Acceleration = FVector3d(0.0f, 0.0f, 0.0f);


	// Turn (rotate around the Z axis - Yaw) the ship if A or D is held
	if (TurnDirection != 0)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw = Rotation.Yaw + TurnDirection * RotationSpeed * DeltaTime;  // Yaw is rotation around the up/down axis this is the Z axis in Unreal
		SetActorRotation(Rotation);
	}

	// Calculate target roll based on turn direction
	float targetRoll = TurnDirection * MaxRollAngle;
	// Smoothly interpolate current roll toward target roll
	CurrentRoll = FMath::FInterpTo(CurrentRoll, targetRoll, DeltaTime, RollSpeed);
	//Set the roll (rotation around the x axis) of the actor Rotation 
	FRotator rotation = GetActorRotation();
	rotation.Roll = CurrentRoll;
	SetActorRotation(rotation);


	// Ascend/Descend the ship if UpArrow or DownArrow is held
	if (AltitudeDirection != 0)
	{
		FVector3d UpVector = GetActorUpVector(); //Get the upward direction of the ship
		//Multiply the UpVector by the direction (based on the up/down keys) and by the Altitude Thrust strength (which is tunable in the editor)
		Acceleration = Acceleration + UpVector * AltitudeDirection * AltitudeThrustStrength;
	}

	// Calculate target pitch based on up/down direction
	float targetPitch = AltitudeDirection * MaxPitchAngle;
	// Smoothly interpolate current pitch toward target pitch
	CurrentPitch = FMath::FInterpTo(CurrentPitch, targetPitch, DeltaTime, PitchSpeed);
	//Set the pitch (rotation around the y axis) of the actor Rotation 
	rotation = GetActorRotation();
	rotation.Pitch = CurrentPitch;
	SetActorRotation(rotation);


	// Calculate and add forward acceleration if thrusting
	if (bIsThrusting)
	{
		//Modify the acceleration for this frame
		FVector3d Forward = GetActorForwardVector();  //Get the direction the ship is pointing in
		Acceleration = Acceleration + Forward * ThrustStrength;  //Set the acceleration based on the direction of the ship
	}

	

	// Update velocity using acceleration
	Velocity = Velocity + Acceleration * DeltaTime;

	//Add to friction if breaking if not use normal friction
	float friction = bIsBraking ? BrakingFriction : Friction;

	// Apply friction (drag)
	Velocity = Velocity - (Velocity * friction);

	// Cap the speed to MaxSpeed
	if (Velocity.Size() > MaxSpeed)
	{
		Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
	}

	//Now handled in player controller class instead
	//printSpeed();

	// Move the ship using the current velocity
	AddActorWorldOffset(Velocity * DeltaTime, true);

}

// Called to bind functionality to input
void AAAWSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	//When you override a method from the Parent class always call the parents implementation to get the default behaviour
	APawn::SetupPlayerInputComponent(PlayerInputComponent);


	// Bind W key for thrust
	PlayerInputComponent->BindKey(EKeys::W, IE_Pressed, this, &AAAWSpaceShip::OnThrustPressed);
	PlayerInputComponent->BindKey(EKeys::W, IE_Released, this, &AAAWSpaceShip::OnThrustReleased);

	// Bind A and D keys for turning
	PlayerInputComponent->BindKey(EKeys::Left, IE_Pressed, this, &AAAWSpaceShip::OnTurnLeftPressed);
	PlayerInputComponent->BindKey(EKeys::Right, IE_Pressed, this, &AAAWSpaceShip::OnTurnRightPressed);

	// Stop turning when A or D is released
	PlayerInputComponent->BindKey(EKeys::Left, IE_Released, this, &AAAWSpaceShip::OnTurnReleased);
	PlayerInputComponent->BindKey(EKeys::Right, IE_Released, this, &AAAWSpaceShip::OnTurnReleased);

	// Bind S key for break
	PlayerInputComponent->BindKey(EKeys::S, IE_Released, this, &AAAWSpaceShip::OnBrakePressed);
	PlayerInputComponent->BindKey(EKeys::S, IE_Released, this, &AAAWSpaceShip::OnBrakeReleased);

	// Bind UpArrow and DownArrow keys for turning
	PlayerInputComponent->BindKey(EKeys::Up, IE_Pressed, this, &AAAWSpaceShip::OnAscendPressed);
	PlayerInputComponent->BindKey(EKeys::Down, IE_Pressed, this, &AAAWSpaceShip::OnDescendPressed);

	// Stop turning when UpArrow or DownArrow is released
	PlayerInputComponent->BindKey(EKeys::Up, IE_Released, this, &AAAWSpaceShip::OnAltitudeReleased);
	PlayerInputComponent->BindKey(EKeys::Down, IE_Released, this, &AAAWSpaceShip::OnAltitudeReleased);

	// Bind Q and E keys for shooting
	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AAAWSpaceShip::OnFire1Pressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AAAWSpaceShip::OnFire2Pressed);

}

void AAAWSpaceShip::SetInputEnabled(bool bIsEnabled)
{
	bCanReceiveInput = bIsEnabled;
}

void AAAWSpaceShip::printSpeed()
{
	FString speedOut = FString(TEXT("Speed: "));
	FString vel = FString::FromInt((int)Velocity.Size());
	FString out = speedOut + vel;
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor(1, 1, 1, 255), out);
}

float AAAWSpaceShip::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	//Call the Super class implementation and store the damage value returned
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float t_ScaledDamage = ActualDamage * DamageMultiplier;
	float t_NewHealth = Health - t_ScaledDamage;

	SetHealth(t_NewHealth);
	HealthAttribute->UpdateHealth(-t_ScaledDamage);

	//Use a UE_LOG to print the actual damage.
	UE_LOG(LogTemp, Display, TEXT("Taking damage: %f"),ActualDamage);
	PlayerController->SetHUDHealth(Health, MaxHealth);

	if (Health <= 0) {
		PlayerController->LoseLife();
	}

	return ActualDamage;

}

const float AAAWSpaceShip::GetMaxHealth()
{
	return MaxHealth;
}

const float AAAWSpaceShip::GetSpeed()
{


	return Velocity.Size();
}

const float AAAWSpaceShip::GetMaxSpeed()
{
	return MaxSpeed;
}

void AAAWSpaceShip::SetHealth(float _input)
{
	if (_input < 0) {
		_input = 0;
	}

	if (_input > MaxHealth) {
		_input = MaxHealth;
	}

	Health = _input;
}

void AAAWSpaceShip::DisableOnDeath()
{
	TheShip->SetVisibility(false, false);
	this->SetActorEnableCollision(false);
	SetInputEnabled(false);

	EngineSound->FadeOut(0.2, 0.5);
	EngineTrail->Deactivate();

	if (ExplosionParticle && ExplosionSound) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionParticle, this->GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, this->GetActorLocation());
	}
	
	PlayerController->SetHUDHealth(Health, MaxHealth);
}

void AAAWSpaceShip::EnableOnRegen()
{
	SetHealth(GetMaxHealth());

	TheShip->SetVisibility(true, false);
	this->SetActorEnableCollision(true);
	SetInputEnabled(true);
	PlayerController->SetHUDHealth(Health, MaxHealth);


}

void AAAWSpaceShip::Regenerate()
{
	DisableOnDeath();

	//Delay using a 2.0f second timer The call a method
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,                      // Think of this as The "Receipt"
		this,                              // The Target Object                              
		&AAAWSpaceShip::EnableOnRegen,      // A reference to the Method to Call     
		RespawnTimer,                      // How long to wait (Seconds)
		false                              // Should it loop?
	);

}

void AAAWSpaceShip::OnThrustPressed()
{
	//If input isn't enabled return early
	if (!bCanReceiveInput)
	{
		return;
	}
	bIsThrusting = true;

	EngineSound->FadeIn(0.5);
	EngineTrail->Activate();


}

void AAAWSpaceShip::OnThrustReleased()
{
	bIsThrusting = false;
	EngineSound->FadeOut(0.2,0.5);
	EngineTrail->Deactivate();
}

void AAAWSpaceShip::OnTurnLeftPressed()
{
	//If input isn't enabled return early
	if (!bCanReceiveInput)
	{
		return;
	}
	TurnDirection = -1;
}

void AAAWSpaceShip::OnTurnRightPressed()
{
	//If input isn't enabled return early
	if (!bCanReceiveInput)
	{
		return;
	}
	TurnDirection = 1;
}

void AAAWSpaceShip::OnTurnReleased()
{


	TurnDirection = 0;
}

void AAAWSpaceShip::OnBrakePressed()
{
	bIsBraking = true;
}

void AAAWSpaceShip::OnBrakeReleased()
{
	bIsBraking = false;
}

void AAAWSpaceShip::OnAscendPressed()
{
	//If input isn't enabled return early
	if (!bCanReceiveInput)
	{
		return;
	}
	AltitudeDirection = 1;
}

void AAAWSpaceShip::OnDescendPressed()
{
	//If input isn't enabled return early
	if (!bCanReceiveInput)
	{
		return;
	}
	AltitudeDirection = -1;
}

void AAAWSpaceShip::OnAltitudeReleased()
{
	AltitudeDirection = 0;

}

void AAAWSpaceShip::OnFire1Pressed()
{
	OnFire(LeftGunSocketName);
}

void AAAWSpaceShip::OnFire2Pressed()
{
	OnFire(RightGunSocketName);
}

void AAAWSpaceShip::OnFire(const FName& SocketName)
{

	// Verify a Projectile class was assigned in the Editor 
	// if no class is assigned we can't spawn anything
	if (ProjectileClass)
	{
		FVector SpawnLocation;
		// Try to find the socket named "LeftGun" on the ship’s static mesh
		const UStaticMeshSocket* Socket = TheShip->GetSocketByName(SocketName);
		// Check if the socket was found
		if (Socket) {
			// Create a Transform to store the location and rotation of the socket
			FTransform SocketTransform;

			// Get the world space transform (position, rotation, scale) of the socket
			// store it in SocketTransform
			Socket->GetSocketTransform(SocketTransform, TheShip);
			SpawnLocation = SocketTransform.GetLocation();							// Get the socket location
		}
		else
		{
			SpawnLocation = GetActorLocation() + GetActorForwardVector() * 2000;   //the ship's current location + a bit
		}




		// Get a reference to the current game world
		UWorld* World = GetWorld();
		//Check to make sure World is not null
		if (World)
		{
			// Configure some spawning rules :
			FActorSpawnParameters SpawnParameters;
			// Identify this ship as the 'Instigator' (responsible for the damage dealt by the projectile).
			SpawnParameters.Instigator = this;
			// Ensure the projectile spawns even if it's currently overlapping another object.
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Instantiate the Projectile:
			World->SpawnActor<AAAWProjectile>(
				ProjectileClass,                                       // The specific type to spawn. (set in the editor)
				SpawnLocation,										   // Where to spawn it (the ship's current location + a bit)
				GetActorRotation(),                                    // Matches the ship's current orientation.
				SpawnParameters                                        // Pass our custom rules into the spawn function
			);
		}

	}

}
