// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
class AAAWRock;

#include "AAWRockSpawner.generated.h"

UCLASS()
class SPACEROCKS3D_AW_API AAAWRockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAWRockSpawner();

private:
	void SpawnRocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	TSubclassOf<AAAWRock> Rock;

	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	int RockCount = 500;

	
	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	float MaxSpawnRadius = 2500;
	
	UPROPERTY(EditAnywhere, Category = "Rock Spawning Configuration Properties");
	float MinSpawnRadius = 500;

 


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
