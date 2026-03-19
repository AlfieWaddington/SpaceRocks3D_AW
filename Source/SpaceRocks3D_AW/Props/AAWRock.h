// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAWRock.generated.h"

class UStaticMesh;


UCLASS()
class SPACEROCKS3D_AW_API AAAWRock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAWRock();

private:
	//Member variables for velocity
	FVector Velocity;

	UPROPERTY(EditAnywhere, Category = "Rock Movement");
	FVector AngularVelocity;

	UPROPERTY(EditAnywhere, Category = "Rock Movement");
	FVector Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,	   // This is the rock's own collision component (e.g. the CollisionBox)
		AActor* OtherActor,				       // The actor that we collided with (could be a Projectile, Wall, Enemy, etc.)
		UPrimitiveComponent* OtherComp,	 // The specific component on the other actor that we hit (like their collision or mesh)
		FVector NormalImpulse,			     // The force of the collision — useful if you want to apply knockback or bounce
		const FHitResult& Hit			       // A treasure chest of collision details: exact location, surface normal, etc.			
	);

	//Static mesh
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> RockMesh;

	//An array of Static Meshes
	UPROPERTY(EditAnywhere, Category = "Rock Properties")
	TArray<TObjectPtr<UStaticMesh>> RockMeshes;

	//Range of possible scales the rocks can have
	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	FVector2D RandomScaleRange = { 0.5,10.0 };

	//Range of possible speeds the rocks can have
	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	FVector2D RandomSpeedRange = { 100.0f,1000.0f };

	//Range of starting angles the rocks can have
	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	FVector2D RandomAngleRange = { -45.0f,45.0f };


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Once the object is initialized this is called - useful for wiring up the collision response
	virtual void PostInitializeComponents() override;

};
