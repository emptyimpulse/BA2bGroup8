// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionTools/SetSpawnPoint.h"

// Sets default values
ASetSpawnPoint::ASetSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObserverSpawnPointComponent = CreateDefaultSubobject<USceneComponent>("ObserverSpawnPointComponent");
	SolverSpawnPointComponent = CreateDefaultSubobject<USceneComponent>("SolverSpawnPointComponent");
	TraitorSpawnPointComponent = CreateDefaultSubobject<USceneComponent>("TraitorSpawnPointComponent");
}

// Called when the game starts or when spawned
void ASetSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASetSpawnPoint::GetObserverSpawnPointLocation()
{
	return ObserverSpawnPointComponent->GetComponentLocation();
}

FVector ASetSpawnPoint::GetSolverSpawnPointLocation()
{
	return SolverSpawnPointComponent->GetComponentLocation();
}

FVector ASetSpawnPoint::GetTraitorSpawnPointLocation()
{
	return TraitorSpawnPointComponent->GetComponentLocation();
}


