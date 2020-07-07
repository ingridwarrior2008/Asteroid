// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UE4 Includes
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/ObjectMacros.h"
// Generated Include
#include "AsteroidActor.generated.h"

class URotatingMovementComponent;
class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;

USTRUCT(Blueprintable)
struct FAsteroidSpeedProperty
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MinimumSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxSpeed;
};

UCLASS()
class ASTEROIDS_API AAsteroidActor : public AActor
{
    GENERATED_BODY()

public:

    AAsteroidActor();
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = Asteroid)
    UParticleSystem* ParticleExplosion;

    UPROPERTY(EditAnywhere, Category = Asteroid)
    int DamageToPlayer;

protected:

    virtual void BeginPlay() override;

private:

    UFUNCTION()
    void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                      int32 OtherBodyIndex);

    void Init();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* AsteroidMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
    USceneComponent* SceneRootComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
    URotatingMovementComponent* RotatingMovementComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
    FAsteroidSpeedProperty AsteroidSpeedProperty;

    UPROPERTY()
    float CurrentAsteroidSpeed;

    UPROPERTY()
    UWorld* World;
};
