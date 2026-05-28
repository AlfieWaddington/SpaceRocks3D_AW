// Fill out your copyright notice in the Description page of Project Settings.


#include "AWAttributeComponent.h"

// Sets default values for this component's properties
UAWAttributeComponent::UAWAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAWAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAWAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAWAttributeComponent::UpdateHealth(float points)
{

	Health += points;
	if (Health < 0) Health = 0;
	if (Health > 100) Health = 100;

	//Use a UE_LOG to print the actual damage.
	UE_LOG(LogTemp, Display, TEXT("Health updated on Attribute Component to %f"), Health);

}

