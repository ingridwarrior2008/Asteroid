// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UE4 Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Generated Include
#include "BulletActor.generated.h"

class AScoreManagerActor;
class UAudioComponent;
class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;


UCLASS()
class ASTEROIDS_API ABulletActor : public AActor
{
    GENERATED_BODY()

public:

    ABulletActor();
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = Bullet)
    UParticleSystem* ParticleExplosion;

    UPROPERTY(EditAnywhere, Category = Bullet)
    USoundBase* ShootSound;
    
protected:

    virtual void BeginPlay() override;

private:

    void Init();

    UFUNCTION()
    void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bullet, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BulletMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bullet, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bullet, meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovementComponent;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpaceShip, meta = (AllowPrivateAccess = "true"))
    UAudioComponent* AudioComponent; 

    UPROPERTY()
    UWorld* World;

    UPROPERTY()
    AScoreManagerActor* ScoreManager;
};
