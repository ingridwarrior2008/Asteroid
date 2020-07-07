// Fill out your copyright notice in the Description page of Project Settings.

//This Include
#include "BulletActor.h"
// Local Includes
#include "AsteroidActor.h"
#include "ScoreManagerActor.h"
// UE4 Includes
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// MARK: - Constructor

ABulletActor::ABulletActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));
	SetRootComponent(BulletMeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(BulletMeshComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

// MARK: - Game LifeCycle

void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// MARK: - Private Methods

void ABulletActor::Init()
{
	World = GetWorld();
	
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnOverlapStart);
		BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABulletActor::OnOverlapEnd);
	}

	if (World)
	{
		AActor *ActorFound = UGameplayStatics::GetActorOfClass(World, AScoreManagerActor::StaticClass());
		ScoreManager = Cast<AScoreManagerActor>(ActorFound);
	}

	if (ShootSound)
	{
		AudioComponent->SetSound(ShootSound);
		AudioComponent->Play();
	}
}

//MARK: - Collision Methods -

void ABulletActor::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && ParticleExplosion)
	{
		if (AAsteroidActor *AsteroidActor = Cast<AAsteroidActor>(OtherActor))
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, ParticleExplosion, AsteroidActor->GetActorLocation());
			AsteroidActor->Destroy();

			if (ScoreManager)
			{
				ScoreManager->IncreaseScore();
			}
			
			Destroy();
		}
	}
	
}

void ABulletActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO: Nothing to do here xD
}

