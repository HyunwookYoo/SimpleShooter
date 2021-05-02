// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

#define OUT

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return; }
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) { return; }

	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	OwnerController->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);

	FVector End = ViewPointLocation + (ViewPointRotation.Vector() * MaxRange);

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, ViewPointLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess)
	{
		FVector ShotDirection = -ViewPointRotation.Vector();
		//DrawDebugPoint(GetWorld(), Hit.Location, 10.f, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
	}

}

