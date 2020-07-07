// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UE4 Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Generated Include
#include "ScoreManagerActor.generated.h"

UCLASS()
class ASTEROIDS_API AScoreManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AScoreManagerActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Score)
	void IncreaseScore();

	UPROPERTY(EditAnywhere, Category = Score)
	int IncrementalScoreValue;

	UPROPERTY(BlueprintReadOnly)
    int CurrentScore;
	
protected:
	
	virtual void BeginPlay() override;	
};
