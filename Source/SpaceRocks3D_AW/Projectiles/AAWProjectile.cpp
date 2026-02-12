// Fill out your copyright notice in the Description page of Project Settings.


#include "AAWProjectile.h"
#include "Components\BoxComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"

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

}

// Called when the game starts or when spawned
void AAAWProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAAWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{



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
	}

}

