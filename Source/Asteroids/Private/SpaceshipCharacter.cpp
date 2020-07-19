// Fill out your copyright notice in the Description page of Project Settings.

//This Include
#include "SpaceshipCharacter.h"

// MARK: - Constructor

ASpaceshipCharacter::ASpaceshipCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpaceShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShipMeshComponent"));
    SpaceShipMeshComponent->SetupAttachment(RootComponent);
}


// MARK: - Game LifeCycle

void ASpaceshipCharacter::BeginPlay()
{
    Super::BeginPlay();
    Init();
}

void ASpaceshipCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASpaceshipCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// MARK: - Public Methods

void ASpaceshipCharacter::YawRotationCharacter(float AxisValue)
{
    if (World && AxisValue != 0.0f)
    {
        const FRotator YawRotation = FRotator(0.0f,
                                              RotationSpeed * AxisValue * World->GetDeltaSeconds(),
                                              0.0f);
        SetActorRotation(YawRotation + GetActorRotation());
    }
}

void ASpaceshipCharacter::MoveForwardCharacter(float AxisValue)
{
    if (AxisValue != 0.0f)
    {
        const FVector ForwardVector = GetActorRotation().Vector();
        AddMovementInput(ForwardVector, AxisValue);
    }
}

void ASpaceshipCharacter::OnTakeDamage_Implementation(int Damage)
{
    ReceiveDamage(Damage);
    if (CurrentHealth < 0)
    {
        OnPlayerDied();
    }
}

// MARK: - Private Methods

void ASpaceshipCharacter::Init()
{
    World = GetWorld();
    CurrentHealth = MaxHealth;
}

void ASpaceshipCharacter::ReceiveDamage(const int Damage)
{
    CurrentHealth = GetCurrentHealth() - Damage;
}
