// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterEnemy.h"
#include "CustomSpaceShooterCharacter.h"

// Sets default values
ASpaceShooterEnemy::ASpaceShooterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
		MeshComp->SetStaticMesh(CubeMesh.Object);

	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

	MeshComp->SetSimulatePhysics(false);  
	MeshComp->SetNotifyRigidBodyCollision(true);
	MeshComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

// Called when the game starts or when spawned
void ASpaceShooterEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShooterEnemy::Tick(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z -= FallSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	if (NewLocation.Z < DestroyBelowZ)
		Destroy();

}

void ASpaceShooterEnemy::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomSpaceShooterCharacter* Player =
		Cast<ACustomSpaceShooterCharacter>(OtherActor);

	if (Player)
	{
		Player->Die();
		Destroy();
	}
		
}



