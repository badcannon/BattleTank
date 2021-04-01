// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"





void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();
	if(GetControlledTank())
	{
		
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimThroughCrosshair();
}


void ATankPlayerController::AimThroughCrosshair() const
{

	if(!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;
	if(GetSightHitRayLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	
	
}


bool ATankPlayerController::GetSightHitRayLocation(FVector& HitLocation) const
{
	int32 ViewPortSizeX,ViewPortSizeY;
	GetViewportSize(ViewPortSizeX,ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation,ViewPortSizeY*CrosshairYLocation);
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation,LookDirection))
	{
		GetLookVectorHitLocation(LookDirection,HitLocation);
	}
	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * RayRange;
	if(GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
	
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Discarded 
	return DeprojectScreenPositionToWorld(ScreenLocation.X,ScreenLocation.Y,CameraWorldLocation,LookDirection);
	
}



ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
	
}
