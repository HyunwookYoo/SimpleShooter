// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "KillAllGameMode.h"
#include "ShooterAIController.h"

void AKillAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (const auto& AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (const auto& Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
