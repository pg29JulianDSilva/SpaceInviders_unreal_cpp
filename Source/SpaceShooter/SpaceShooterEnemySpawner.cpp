// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterEnemySpawner.h"
#include "SpaceShooterEnemy.h"
#include "CustomSpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ASpaceShooterEnemySpawner::ASpaceShooterEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObstacleClass = ASpaceShooterEnemy::StaticClass();

}

// Called when the game starts or when spawned
void ASpaceShooterEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimer, this,
		&ASpaceShooterEnemySpawner::SpawnObstacle,
		InitialSpawnInterval, true);
	
}

void ASpaceShooterEnemySpawner::SpawnObstacle()
{
	ACustomSpaceShooterGameMode* thisGame = Cast<ACustomSpaceShooterGameMode>(UGameplayStatics::GetGameMode(this));
	if (thisGame && thisGame->bGameOver) return;

	if (ObstacleClass) return;

	float RandX = FMath::FRandRange(-SpawnRangeX, SpawnRangeX);
	float RandY = FMath::FRandRange(-SpawnRangeY, SpawnRangeY);
	FVector SpawnLocation(RandX, RandY, SpawnHeight);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ObstacleClass, SpawnLocation,
		FRotator::ZeroRotator, Params);

	UpdateDifficulty();
}

void ASpaceShooterEnemySpawner::UpdateDifficulty()
{
	ElapsedTime += GetWorldTimerManager().GetTimerRate(SpawnTimer);

	float Alpha = FMath::Clamp(ElapsedTime / DifficultyRampTime, 0.f, 1.f);
	float NewInterval = FMath::Lerp(InitialSpawnInterval, MinSpawnInterval, Alpha);


	GetWorldTimerManager().SetTimer(SpawnTimer, this,
		&ASpaceShooterEnemySpawner::SpawnObstacle, NewInterval, true);
}

