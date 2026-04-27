// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSpaceShooterCharacter.h"
#include "SpaceShooterHealthComponent.h"
#include "CustomSpaceShooterController.h"
#include "CustomSpaceShooterGameMode.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

// Sets default values
ACustomSpaceShooterCharacter::ACustomSpaceShooterCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<USpaceShooterHealthComponent>(TEXT("HealthComponent"));

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ACustomSpaceShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsDead = false;

	if (APlayerController* PC = Cast<ACustomSpaceShooterController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	FVector StartLoc = GetActorLocation();
	FixedX = StartLoc.X;          
	StartLoc.Z = 0.f;
	SetActorLocation(StartLoc);

}

void ACustomSpaceShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACustomSpaceShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDead) return;

	FVector Loc = GetActorLocation();
	Loc.X = FixedX;                                            
	Loc.Y = FMath::Clamp(Loc.Y, -ArenaHalfWidth, ArenaHalfWidth);
	SetActorLocation(Loc);

}

void ACustomSpaceShooterCharacter::Die()
{
	if (bIsDead) return;
	bIsDead = true;

	ACustomSpaceShooterController* thisController = Cast<ACustomSpaceShooterController>(GetController());
	if (thisController) thisController->DisableInput(thisController);

	ACustomSpaceShooterGameMode* thisGamemode = Cast<ACustomSpaceShooterGameMode>(UGameplayStatics::GetGameMode(this));
	if (thisGamemode) thisGamemode->OnPlayerDead();

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}


// Called to bind functionality to input
void ACustomSpaceShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveInput)
		{
			EIC->BindAction(MoveInput, ETriggerEvent::Triggered,
				this, &ACustomSpaceShooterCharacter::OnMovementInputReceived);
		}
	}

}

void ACustomSpaceShooterCharacter::OnMovementInputReceived(const FInputActionValue& Value)
{
	if (bIsDead) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const float HorizontalInput = MovementVector.X; 

	AddMovementInput(FVector(0.f, 1.f, 0.f), HorizontalInput);
}

