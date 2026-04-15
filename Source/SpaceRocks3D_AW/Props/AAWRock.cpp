// Fill out your copyright notice in the Description page of Project Settings.

#include "Props/AAWRock.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAAWRock::AAAWRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Mesh"));
	SetRootComponent(RockMesh);
	RockMesh->SetCollisionProfileName("Rock");
	RockMesh->SetSimulatePhysics(true);
	RockMesh->SetEnableGravity(false);
	RockMesh->SetMassScale(NAME_None, 0.1f);

	// Enable collision notifications so we can respond to impacts (e.g., OnComponentHit events)
	RockMesh->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void AAAWRock::BeginPlay()
{
	Super::BeginPlay();
	
	//Select a random mesh
	if (RockMeshes.Num() > 0)
	{
		const int i = FMath::RandRange(0, RockMeshes.Num() - 1);
		RockMesh->SetStaticMesh(RockMeshes[i]);
	}

	//Choose a random scale and apply
	const float Scale = FMath::FRandRange(RandomScaleRange.GetMin(), RandomScaleRange.GetMax());
	const FVector Scale3D = FVector(Scale, Scale, Scale);
	RockMesh->SetWorldScale3D(Scale3D);


	//Get a random unit vector for direction
	const FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
	//Get a random speed between 100 and 1000??
	const float RandomSpeed = FMath::FRandRange(RandomSpeedRange.GetMin(),RandomSpeedRange.GetMax());
	//Create a velocity vector from the above
	Velocity = RandomUnitVector * RandomSpeed;

	//Create a random number between -45 and +45
	const float RandomAngle = FMath::FRandRange(RandomAngleRange.GetMin(),RandomAngleRange.GetMax());
	//Use the random Angle to create a random rotation
	AngularVelocity = FVector(RandomAngle, RandomAngle, RandomAngle);  //You can actually do this: FVector(RandomAngle);

	//Use the vectors to set the physics of the rocks
	RockMesh->SetPhysicsLinearVelocity(Velocity);
	RockMesh->SetPhysicsAngularVelocityInDegrees(AngularVelocity);


}

void AAAWRock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor->ActorHasTag("Spaceship")) {

		// Convert the projectile's rotation into a direction vector to indicate where the force came from
		FVector HitDirection = GetActorRotation().Vector();

		// Retrieve the physical mass of the rock component (larger scale = higher mass)
		const float RockMass = HitComp->GetMass();

		// Calculate final damage: Start with base and add a fraction of the mass 
		// so heavier rocks deal significantly more damage. (Could the fraction be exposed to the editor)
		const float ScaledDamage = BaseDamage + (RockMass * DamageScale);

		UGameplayStatics::ApplyPointDamage(
			OtherActor,                 // The Actor that will receive the damage (the victim)
			ScaledDamage,                      // The amount of damage to apply to the OtherActor
			HitDirection,               // The direction the damage is coming from (useful for knockback)
			Hit,                        // The FHitResult containing exact impact data (location, normal, etc.)
			GetInstigatorController(),  // The Controller responsible for the damage (useful for kill tracking)
			this,                       // The Actor actually causing the damage (the projectile itself)
			DamageTypeClass             // The class defining the "type" of damage (e.g., Fire, Explosive, Kinetic etc)
		);
	}


	if (OtherActor->ActorHasTag("Projectile")) {
		this->Destroy();
	}

}

// Called every frame
void AAAWRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAAWRock::PostInitializeComponents()
{

	Super::PostInitializeComponents();

	//Bind the OnHit Method to the OnComponentHit delegate 
	RockMesh->OnComponentHit.AddDynamic(this, &AAAWRock::OnHit);

}
