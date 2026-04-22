// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSpaceShooterCharacter.h"
#include "SpaceShooterHealthComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

// Sets default values
ACustomSpaceShooterCharacter::ACustomSpaceShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<USpaceShooterHealthComponent>(TEXT("HealthComponent"));

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called when the game starts or when spawned
void ACustomSpaceShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomSpaceShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomSpaceShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			if (MoveInput)
			{
				EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ACustomSpaceShooterCharacter::OnMovementInputReceived);
			}
		}
	}

}

void ACustomSpaceShooterCharacter::OnMovementInputReceived(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller)
	{
		const FVector ForwardVector = GetActorForwardVector();
		const FVector RightVector = GetActorRightVector();
		AddMovementInput(ForwardVector, MovementVector.Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

