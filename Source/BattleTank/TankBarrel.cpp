// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
	



void UTankBarrel::Elevate(float RawRelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();	
	auto RelativeSpeed = FMath::Clamp<float>(RawRelativeSpeed,-1.0f,1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawElevation,MinElevationDegrees,MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0,0));
	UE_LOG(LogTemp,Warning,TEXT("%f:DegreesPerSeconds -> %f"),Time,Elevation);
	
}
