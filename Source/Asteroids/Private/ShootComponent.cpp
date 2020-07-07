// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

// MARK: - Constructor

UShootComponent::UShootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// MARK: - Game LifeCycle

void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// MARK: - Public Methods

void UShootComponent::Shoot(TArray<FVector> StartLocations, FRotator OwnerRotation)
{
	if (ensureMsgf(BulletActorClass, TEXT("BulletActor should not be null")))
	{
		for (FVector Location : StartLocations)
		{

			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
			FTransform Transform = FTransform(OwnerRotation, Location, FVector::OneVector);
			
			ABulletActor* BulletActor = GetWorld()->SpawnActor<ABulletActor>(BulletActorClass, Transform, ActorSpawnParameters);	
		}
	}
}