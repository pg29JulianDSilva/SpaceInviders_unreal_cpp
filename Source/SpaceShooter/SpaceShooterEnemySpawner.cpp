// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterEnemySpawner.h"

// Sets default values
ASpaceShooterEnemySpawner::ASpaceShooterEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceShooterEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShooterEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

