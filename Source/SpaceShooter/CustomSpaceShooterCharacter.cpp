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
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "SpaceShooterEnemy.h"
#include "EnhancedInputComponent.h"

// Sets default values
ACustomSpaceShooterCharacter::ACustomSpaceShooterCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<USpaceShooterHealthComponent>(TEXT("HealthComponent"));

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bRequestedMoveUseAcceleration = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
	
	GetCharacterMovement()->MaxAcceleration = 99999.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 99999.f;
	GetCharacterMovement()->BrakingFrictionFactor = 0.f;
	GetCharacterMovement()->BrakingFriction = 0.f;

}

// Called when the game starts or when spawned
void ACustomSpaceShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
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

void ACustomSpaceShooterCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if(ASpaceShooterEnemy* enemy = Cast<ASpaceShooterEnemy>(OtherActor))
		{
			Die();
		}
	}
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

