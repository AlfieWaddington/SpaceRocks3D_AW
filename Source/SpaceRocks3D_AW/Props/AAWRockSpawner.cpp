// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/AAWRockSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "AAWRock.h"


// Sets default values
AAAWRockSpawner::AAAWRockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AAAWRockSpawner::SpawnRocks()
{

	
		//ToDo: Check to see if the RockClass has been set in the editor 
		// if it hasn't then return early, you can use a Log to the console as well if you like.
	if (Rock) {



		//Loop over the Quantity of rocks that are to be created
		for (int i = 0; i < RockCount; i++)
		{
			//ToDo: Create a random unit vector for the direction 
			const FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();

			//ToDo: Get a random number between MinSpawnRadius and MaxSpawnRadius for the distance
			float RandomDistance = FMath::RandRange(MinSpawnRadius, MaxSpawnRadius);

			//ToDo: Create a random Offset vector from the above direction and distance.
			FVector Offset = RandomUnitVector * RandomDistance;

			//ToDo: Create a spawn location using the location of the spawner + your Random offset vector
			FVector SpawnLocation = GetActorLocation() + Offset;

			//Create some SpawnParameters
			FActorSpawnParameters SpawnParams;
			//Don't let the rock spawn if it is colliding and can't be adjusted not to
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//Spawn the Rock 
			GetWorld()->SpawnActor<AAAWRock>(Rock, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		}


	}
	else {
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor(1, 1, 1, 255), "No rock class set for rock spawner");
		return;
	}




}

// Called when the game starts or when spawned
void AAAWRockSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnRocks();

}

// Called every frame
void AAAWRockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

