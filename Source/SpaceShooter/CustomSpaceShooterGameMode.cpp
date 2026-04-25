// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSpaceShooterGameMode.h"
#include "CustomSpaceShooterController.h"
#include "CustomSpaceShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

ACustomSpaceShooterGameMode::ACustomSpaceShooterGameMode()
{
	PlayerControllerClass = ACustomSpaceShooterController::StaticClass();
	DefaultPawnClass = ACustomSpaceShooterCharacter::StaticClass();
}

void ACustomSpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	bGameOver = false;
}

void ACustomSpaceShooterGameMode::OnPlayerDead()
{
	if (bGameOver) return;
	bGameOver = true;
	
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 5, FColor::Black, "GAME OVER");

	FTimerHandle RestartTimer;
	GetWorldTimerManager().SetTimer(RestartTimer, [this]()
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
	}, 2.0f, false);

}




