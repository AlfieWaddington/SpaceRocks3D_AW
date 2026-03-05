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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static mesh
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> RockMesh;

	//An array of Static Meshes
	UPROPERTY(EditAnywhere, Category = "Rock Properties")
	TArray<TObjectPtr<UStaticMesh>> RockMeshes;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
