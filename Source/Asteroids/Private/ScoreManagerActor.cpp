// Fill out your copyright notice in the Description page of Project Settings.

//This Include
#include "ScoreManagerActor.h"

// MARK: - Constructor

AScoreManagerActor::AScoreManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IncrementalScoreValue = 1;
}

// MARK: - Game LifeCycle

void AScoreManagerActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AScoreManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// MARK: - Public Methods

void AScoreManagerActor::IncreaseScore()
{
	CurrentScore += IncrementalScoreValue;
}

