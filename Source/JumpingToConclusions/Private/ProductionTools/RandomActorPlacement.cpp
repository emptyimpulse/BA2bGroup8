// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionTools/RandomActorPlacement.h"

#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARandomActorPlacement::ARandomActorPlacement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshChoice = 0;
}

// Called when the game starts or when spawned
void ARandomActorPlacement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomActorPlacement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARandomActorPlacement::RandomiseActor()
{
	StaticMesh->SetStaticMesh(StaticMeshOptions[MeshChoice]);
	if (bRandomRotation)
	{
		FRotator RotationVector = FMath::VRand().Rotation();
		StaticMesh->SetRelativeRotation(RotationVector);
	}
	if (bRandomLocation)
	{
		SpawnBounds = this->GetActorLocation();
		FVector SpawnVector;
		SpawnVector.X = FMath::FRandRange(SpawnBounds.X - 100, SpawnBounds.X + 100);
		SpawnVector.Y = FMath::FRandRange(SpawnBounds.Y - 100, SpawnBounds.Y + 100);
		SpawnVector.Z = SpawnBounds.Z;
		StaticMesh->SetRelativeLocation(SpawnVector);
	}
	if (bRandomScale)
	{
		FVector SpawnVector;
		SpawnVector.X = FMath::FRandRange(.5,1.5);
		SpawnVector.Y = FMath::FRandRange(.5,1.5);
		SpawnVector.Z = FMath::FRandRange(.5,1.5);
		StaticMesh->SetRelativeScale3D(SpawnVector);
	}
}

