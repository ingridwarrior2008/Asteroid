// Fill out your copyright notice in the Description page of Project Settings.

//This Include
#include "SpawnAsteroidManagerActor.h"
// Local Includes

// UE4 Includes
#include "TimerManager.h"

// MARK: - Constructor
ASpawnAsteroidManagerActor::ASpawnAsteroidManagerActor()
{
    PrimaryActorTick.bCanEverTick = true;
    NumSpawnAtSameTime = 1;
}

// MARK: - Game LifeCycle

void ASpawnAsteroidManagerActor::BeginPlay()
{
    Super::BeginPlay();
    Init();
}

void ASpawnAsteroidManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorldTimerManager().ClearTimer(TimerHandle);
    Super::EndPlay(EndPlayReason);
}


void ASpawnAsteroidManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// MARK: - Private Methods

void ASpawnAsteroidManagerActor::Init()
{
    World = GetWorld();
    GetWorldTimerManager().SetTimer(TimerHandle,
                                    this,
                                    &ASpawnAsteroidManagerActor::OnSpawnAsteroid,
                                    SpawnInterval,
                                    true,
                                    DelayAfterStart);
}

void ASpawnAsteroidManagerActor::OnSpawnAsteroid()
{
    if (World && AsteroidClass && SpawnPoints.Num() > 0)
    {
        for (int i = 0; i < NumSpawnAtSameTime; i++)
        {
            FActorSpawnParameters ActorSpawnParameters;
            ActorSpawnParameters.SpawnCollisionHandlingOverride =
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            const int SpawnPointIndex = GetRandomPoint();
            ATargetPoint* SelectedPoint = SpawnPoints[SpawnPointIndex];

            const FTransform Transform = FTransform(SelectedPoint->GetActorRotation(),
                                                    SelectedPoint->GetActorLocation(),
                                                    FVector::OneVector);

            World->SpawnActor<AAsteroidActor>(AsteroidClass, Transform, ActorSpawnParameters);
        }
    }
}


int ASpawnAsteroidManagerActor::GetRandomPoint() const
{
    if (SpawnPoints.Num() > 0)
    {
        return FMath::RandRange(0, SpawnPoints.Num() - 1);
    }
    return 0;
}
