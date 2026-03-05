// Fill out your copyright notice in the Description page of Project Settings.

#include "Props/AAWRock.h"
#include "Engine/StaticMesh.h"


// Sets default values
AAAWRock::AAAWRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Mesh"));
	SetRootComponent(RockMesh);
	RockMesh->SetCollisionProfileName("Rock");
	RockMesh->SetSimulatePhysics(true);
	RockMesh->SetEnableGravity(false);
	RockMesh->SetMassScale(NAME_None, 0.1f);

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
	const float Scale = FMath::FRandRange(0.5, 10.0);
	const FVector Scale3D = FVector(Scale, Scale, Scale);
	RockMesh->SetWorldScale3D(Scale3D);

}

// Called every frame
void AAAWRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

