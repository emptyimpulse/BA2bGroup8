// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PuzzleSpawnManager.h"

#include "InstancedStaticMeshDelegates.h"

// Sets default values
APuzzleSpawnManager::APuzzleSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPointOne = CreateDefaultSubobject<USceneComponent>("SpawnPointOne");
	SpawnPointTwo = CreateDefaultSubobject<USceneComponent>("SpawnPointTwo");
	SpawnPointThree = CreateDefaultSubobject<USceneComponent>("SpawnPointThree");

	SpawnLocations.Add(SpawnPointOne);
	SpawnLocations.Add(SpawnPointTwo);
	SpawnLocations.Add(SpawnPointThree);
}

// Called when the game starts or when spawned
void APuzzleSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	SRand = FRandomStream();
	SRand.Initialize(DateInSeconds);
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
		if (SpawnedPuzzles.Num() != 0)
		{
			for (APuzzleTempCube* SpawnedActor : SpawnedPuzzles)
			{
				SpawnedActor->Destroy();
			}
			SpawnedPuzzles.RemoveAll([](AActor* Removed)
			{
				return Removed == nullptr||!IsValid(Removed);
			});
		}

		for (int32 i = 0; i <= SpawnLocations.Num()-1; i++)
		{
			//terrible code im sorry
			int8 RandomPuzzleSpawnIndex = SRand.RandRange(0,2);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			TSubclassOf<APuzzleTempCube> PuzzleClass = SpawnedActors[RandomPuzzleSpawnIndex];
			
			APuzzleTempCube* TempPuzzle = GetWorld()->SpawnActor<APuzzleTempCube>(
				PuzzleClass,
				SpawnLocations[i]->GetComponentLocation(),
				FRotator::ZeroRotator,
				SpawnParams);

			TempPuzzle->SetPuzzleIndex(i);
			SpawnedPuzzles.Add(TempPuzzle);
		}
	}
}

