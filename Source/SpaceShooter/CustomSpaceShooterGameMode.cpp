// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSpaceShooterGameMode.h"
#include "CustomSpaceShooterController.h"
#include "CustomSpaceShooterCharacter.h"

ACustomSpaceShooterGameMode::ACustomSpaceShooterGameMode()
{
	PlayerControllerClass = ACustomSpaceShooterController::StaticClass();
	DefaultPawnClass = ACustomSpaceShooterCharacter::StaticClass();
}
