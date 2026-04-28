// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CustomSpaceShooterCharacter.generated.h"

class USpaceShooterHealthComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SPACESHOOTER_API ACustomSpaceShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomSpaceShooterCharacter();

public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	void Die();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ArenaHalfWidth = 480.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpaceShooterHealthComponent* HealthComponent;

private:

	void OnMovementInputReceived(const FInputActionValue& Value);

	float FixedX = 0.f;
	bool bIsDead = false;

};
