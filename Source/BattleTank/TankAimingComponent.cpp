// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	const FString TankName = GetOwner()->GetName();
	if(!Barrel)
	{
		return;
	}
	else
	{
		// const FString BarrelLocation = Barrel->GetComponentLocation().ToString();
		FVector LaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


		//Calculate LaunchVelocity
		FCollisionResponseParams ResponseParams;
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
            this,
            LaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace);
		if(bHaveAimSolution)
		{
			auto AimDirection = LaunchVelocity.GetSafeNormal();
			// UE_LOG(LogTemp,Warning,TEXT("AimDirection : %s"),*AimDirection.ToString());
			MoveBarrelTowards(AimDirection);

 		}
	
		// UE_LOG(LogTemp,Warning,TEXT("Tank : %s is aiming at : %s , From : %s"),*TankName,*HitLocation.ToString(),*BarrelLocation);

		

	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)  
{

		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;
		Barrel->Elevate(DeltaRotator.Pitch);
		
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

