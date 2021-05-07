// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "ShooterPlayerController.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDClass);
	if (HUDScreen == nullptr) { return; }
	HUDScreen->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}	
	}

	HUDScreen->RemoveFromViewport();
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
