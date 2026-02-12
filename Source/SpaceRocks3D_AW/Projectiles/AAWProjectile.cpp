// Fill out your copyright notice in the Description page of Project Settings.


#include "AAWProjectile.h"
#include "Components\BoxComponent.h"
#include "GameFramework\DamageType.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "Kismet\GameplayStatics.h"
#include "NiagaraComponent.h"
#include "Sound\SoundBase.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components\AudioComponent.h"

// Sets default values
AAAWProjectile::AAAWProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("The Collision Box Component"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionProfileName(TEXT("Projectile"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("The projectile movement component"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;

	InitialLifeSpan = 12.0f;

	Tracer = CreateDefaultSubobject<UNiagaraComponent>(TEXT("The particle effect that traces the projectile"));
	Tracer->SetupAttachment(CollisionBox);

}

// Called when the game starts or when spawned
void AAAWProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (FireSound) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, this->GetActorLocation());
	}
	
	
}

void AAAWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	

	// Convert the projectile's rotation into a direction vector to indicate where the force came from
	FVector HitDirection = GetActorRotation().Vector();

	UGameplayStatics::ApplyPointDamage(
		OtherActor,                 // The Actor that will receive the damage (the victim)
		50.0f,                      // The amount of damage to apply to the OtherActor
		HitDirection,               // The direction the damage is coming from (useful for knockback)
		Hit,                        // The FHitResult containing exact impact data (location, normal, etc.)
		GetInstigatorController(),  // The Controller responsible for the damage (useful for kill tracking)
		this,                       // The Actor actually causing the damage (the projectile itself)
		DamageTypeClass             // The class defining the "type" of damage (e.g., Fire, Explosive, Kinetic etc)
	);

	if (ExplosionParticle && ExplosionSound) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ExplosionParticle,this->GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, this->GetActorLocation());
	}



	this->Destroy();

 }

// Called every frame
void AAAWProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAAWProjectile::PostInitializeComponents()
{

	Super::PostInitializeComponents();

	//Bind the OnHit Method to the OnComponentHit delegate 
	CollisionBox->OnComponentHit.AddDynamic(this, &AAAWProjectile::OnHit);

	// Safety check: Make sure we have a collider and an owner (Instigator)
	if (CollisionBox && GetInstigator())
	{
		// Tell our collider to ignore the ship that fired us
		CollisionBox->IgnoreActorWhenMoving(GetInstigator(), true);

		// Tell our collider to ignore the ship that fired us
		CollisionBox->IgnoreActorWhenMoving(this, true);
	}

}

