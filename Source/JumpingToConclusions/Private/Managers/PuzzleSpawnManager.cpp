// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PuzzleSpawnManager.h"

// Sets default values
APuzzleSpawnManager::APuzzleSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPointOne = CreateDefaultSubobject<USceneComponent>("SpawnPointOne");
	SpawnPoinTwo = CreateDefaultSubobject<USceneComponent>("SpawnPointTwo");
	SpawnPointThree = CreateDefaultSubobject<USceneComponent>("SpawnPointThree");

	SpawnLocations.Add(SpawnPointOne);
	SpawnLocations.Add(SpawnPoinTwo);
	SpawnLocations.Add(SpawnPointThree);
}

// Called when the game starts or when spawned
void APuzzleSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	DateInSeconds = FDateTime::Now().ToUnixTimestamp();
}

// Called every frame
void APuzzleSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleSpawnManager::SpawnRandomPuzzles()
{
	if (HasAuthority())
	{
		FRandomStream SRand = FRandomStream();
		SRand.Initialize(DateInSeconds);
		for (int i = 0; i <= SpawnLocations.Num()-1; i++)
		{
			int8 RandomPuzzleSpawnIndex = SRand.RandRange(0,SpawnedActors.Num()-1);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			TSubclassOf<APuzzleTempCube> PuzzleClass = SpawnedActors[RandomPuzzleSpawnIndex];
			
			APuzzleTempCube* SpawnedPuzzle = GetWorld()->SpawnActor<APuzzleTempCube>(
				PuzzleClass,
				SpawnLocations[i]->GetComponentLocation(),
				FRotator::ZeroRotator,
				SpawnParams);
		}
	}
}

