// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Barrel Elevation Rotation 
UCLASS(ClassGroup=Custom,meta=(BlueprintSpawnableComponent),HideCategories=(Collision))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
	void Elevate(float RealtiveSpeed);

	private:
	UPROPERTY(EditAnywhere,Category=Setup)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere,Category=Setup)
	float MaxElevationDegrees = 40;
	UPROPERTY(EditAnywhere,Category=Setup)
	float MinElevationDegrees = 0;
	
};
