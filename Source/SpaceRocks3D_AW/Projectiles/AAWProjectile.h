// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UDamageType;
class UNiagaraComponent;
class USoundBase;
class UAudioComponent;
class UNiagaraSystem;

#include "AAWProjectile.generated.h"



UCLASS()
class SPACEROCKS3D_AW_API AAAWProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAWProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Collision Box
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	//The projectile movement component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DamageTypeClass;


	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,	   // This is the projectile's own collision component (e.g. the CollisionBox)
		AActor* OtherActor,				       // The actor that we collided with (could be a Rock, Wall, Enemy, etc.)
		UPrimitiveComponent* OtherComp,	 // The specific component on the other actor that we hit (like their collision or mesh)
		FVector NormalImpulse,			     // The force of the collision — useful if you want to apply knockback or bounce
		const FHitResult& Hit			       // A treasure chest of collision details: exact location, surface normal, etc.			
	);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> Tracer;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UNiagaraSystem> ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USoundBase> FireSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Once the object is initialized this is called - useful for wiring up the collision response
	virtual void PostInitializeComponents() override;

};
