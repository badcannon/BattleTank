// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{

	Super::BeginPlay();
	if(!GetControlledTank())
	{
		UE_LOG(LogTemp,Error,TEXT("Tank AI controller NOT Initalized  "));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Tank AI controller Initalized :%s"),*GetControlledTank()->GetName());
		
	}

	if(!GetPlayerTank())
	{
		UE_LOG(LogTemp,Error,TEXT("Tank AI controller can not find player tank  "));
		
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Tank AI controller found :%s"),*GetPlayerTank()->GetName());
	}

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAtPlayerTank();
}


void ATankAIController::AimAtPlayerTank() const
{

	if(!GetControlledTank())
	{
		return;
	}
	if(GetPlayerTank())
	{
		FVector HitLocation =GetPlayerTank()->GetActorLocation(); 
		GetControlledTank()->AimAt(HitLocation);
	}
}


ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
	
}


ATank* ATankAIController::GetPlayerTank() const
{

	return  Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

