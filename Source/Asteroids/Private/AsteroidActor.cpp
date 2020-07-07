// Fill out your copyright notice in the Description page of Project Settings.

//This Include
#include "AsteroidActor.h"
// Local Includes
#include "SpaceshipCharacter.h"
// UE4 Includes
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// MARK: - Constructor

AAsteroidActor::AAsteroidActor()
{
	PrimaryActorTick.bCanEverTick = true;
	AsteroidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMeshComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	AsteroidMeshComponent->SetupAttachment(RootComponent);
	SphereComponent->SetupAttachment(RootComponent);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

// MARK: - Game LifeCycle

void AAsteroidActor::BeginPlay()
{
	Super::BeginPlay();
	Init();
}


void AAsteroidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * CurrentAsteroidSpeed * DeltaTime);
}

// MARK: - Private Methods

void AAsteroidActor::Init()
{
	CurrentAsteroidSpeed = FMath::RandRange(AsteroidSpeedProperty.MinimumSpeed, AsteroidSpeedProperty.MaxSpeed);

	World = GetWorld();
	
	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidActor::OnOverlapStart);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAsteroidActor::OnOverlapEnd);
	}
}


//MARK: - Collision Methods -

void AAsteroidActor::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && ParticleExplosion)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UDamageInterface::StaticClass()))
		{
			IDamageInterface::Execute_OnTakeDamage(OtherActor, DamageToPlayer);
			UGameplayStatics::SpawnEmitterAtLocation(World, ParticleExplosion, GetActorLocation());
			Destroy();
		}
	}
}

void AAsteroidActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    //TODO: Nothing to do here xD
}