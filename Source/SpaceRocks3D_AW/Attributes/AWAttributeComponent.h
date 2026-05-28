// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AWAttributeComponent.generated.h"

// Called whenever health changes (used by HUD, etc.)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEROCKS3D_AW_API UAWAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAWAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.0f;

	float Health = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateHealth(float points);

	// Event triggered when health changes (Other class's can listen to this)
	// BlueprintAssignable means Blueprints can drag off a pin and say "Bind Event"
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

};
