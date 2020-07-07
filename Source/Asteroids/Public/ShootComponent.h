// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// UE4 Includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// Local Includes
#include "BulletActor.h"
// Generated Include
#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class ASTEROIDS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UShootComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Shoot(TArray<FVector> StartLocations, FRotator OwnerRotation);

	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<ABulletActor> BulletActorClass;

protected:
	virtual void BeginPlay() override;

};
