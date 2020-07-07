// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// UE4 Includes
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
// Local Includes
#include "AsteroidActor.h"
// Generated Include
#include "SpawnAsteroidManagerActor.generated.h"

UCLASS()
class ASTEROIDS_API ASpawnAsteroidManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnAsteroidManagerActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<ATargetPoint*> SpawnPoints;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawn)
	TSubclassOf<AAsteroidActor> AsteroidClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawn)
	float DelayAfterStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawn)
	float SpawnInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawn, meta = (ClampMin = "1", ClampMax = "10"))
	int NumSpawnAtSameTime;

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	void Init();
	int GetRandomPoint() const;
	
	UFUNCTION()
	void OnSpawnAsteroid();
	
	FTimerHandle TimerHandle;

	UPROPERTY()
	UWorld* World;
};
