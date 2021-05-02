// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* ImpactEffect = nullptr;
};
