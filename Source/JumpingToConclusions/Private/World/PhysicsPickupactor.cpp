// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PhysicsPickupactor.h"

// Sets default values
APhysicsPickupactor::APhysicsPickupactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void APhysicsPickupactor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called every frame
void APhysicsPickupactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

