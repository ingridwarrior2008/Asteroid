// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UE4 Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
// Local Includes
#include "DamageInterface.h"
// Generated Include
#include "SpaceshipCharacter.generated.h"

UCLASS()
class ASTEROIDS_API ASpaceshipCharacter : public ACharacter, public IDamageInterface
{
    GENERATED_BODY()

public:

    ASpaceshipCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void OnTakeDamage_Implementation(int Damage) override;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void OnPlayerDied();

    UFUNCTION(BlueprintCallable)
    void YawRotationCharacter(float AxisValue);

    UFUNCTION(BlueprintCallable)
    void MoveForwardCharacter(float AxisValue);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpaceShip)
    float RotationSpeed;

    UPROPERTY(BlueprintReadWrite, Category = SpaceShip)
    bool bCanStartShooting;

    UPROPERTY(EditAnywhere, Category = SpaceShip)
    int MaxHealth;

    UPROPERTY(BlueprintReadWrite, Category = SpaceShip)
    int CurrentHealth;

protected:

    virtual void BeginPlay() override;

private:

    void Init();
    void ReceiveDamage(const int Damage);
    float GetCurrentHealth() const { return  CurrentHealth; }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpaceShip, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* SpaceShipMeshComponent;

    UPROPERTY()
    UWorld* World;
};
