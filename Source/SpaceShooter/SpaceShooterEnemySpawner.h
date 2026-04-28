// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterEnemySpawner.generated.h"

UCLASS()
class SPACESHOOTER_API ASpaceShooterEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceShooterEnemySpawner();
	virtual void BeginPlay() override;

protected:
	// Called when the game starts or when spawned

    UPROPERTY(EditAnywhere, Category = "Spawner")
    TSubclassOf<ASpaceShooterEnemy> ObstacleClass;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnRangeX = 500.f;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnRangeY = 500.f;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnHeight = 800.f;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float InitialSpawnInterval = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float MinSpawnInterval = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float DifficultyRampTime = 60.f;

private:	
    FTimerHandle SpawnTimer;
    float ElapsedTime = 0.f;

    void SpawnObstacle();
    void UpdateDifficulty();
};
