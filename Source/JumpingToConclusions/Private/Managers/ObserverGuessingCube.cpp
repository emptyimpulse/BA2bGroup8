// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ObserverGuessingCube.h"

#include "World/ObeserverGuessingActor.h"

// Sets default values
AObserverGuessingCube::AObserverGuessingCube()
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
void AObserverGuessingCube::BeginPlay()
{
	Super::BeginPlay();
	DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	SRand = FRandomStream();
	SRand.Initialize(DateInSeconds);
}

// Called every frame
void AObserverGuessingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObserverGuessingCube::SpawnObserverTraitorPickers()
{
	if (HasAuthority())
	{
		TArray<int32> RandomPuzzleSpawn;

		RandomPuzzleSpawn.Add(0);
		RandomPuzzleSpawn.Add(1);
		RandomPuzzleSpawn.Add(2);
		
		for (int32 i = RandomPuzzleSpawn.Num() - 1; i > 0; i--)
		{
			int32 j = SRand.FRandRange(0, RandomPuzzleSpawn.Num() - 1);
			int32 temp = RandomPuzzleSpawn[i];
			RandomPuzzleSpawn[i] = RandomPuzzleSpawn[j];
			RandomPuzzleSpawn[j] = temp;
		}

		AJTCGameState* CurrentGameState =  GetWorld()->GetGameStateChecked<AJTCGameState>();
		if (SpawnedTraitorPickers.Num() != 0)
		{
			for (AObeserverGuessingActor* SpawnedActor : SpawnedTraitorPickers)
			{
				SpawnedActor->Destroy();
			}
			SpawnedTraitorPickers.RemoveAll([](AActor* Removed)
			{
				return Removed == nullptr||!IsValid(Removed);
			});
		}

		for (int32 i = 0; i <= SpawnLocations.Num()-1; i++)
		{
			//terrible code im sorry
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			
			AObeserverGuessingActor* TraitorPicker = GetWorld()->SpawnActor<AObeserverGuessingActor>(
				ObeserverGuessingActorClass,
				SpawnLocations[i]->GetComponentLocation(),
				FRotator::ZeroRotator,
				SpawnParams);

			APlayerState* SpecificController = CurrentGameState->PuzzlersControllers[RandomPuzzleSpawn[i]];
			TraitorPicker->ChosenPlayerController = SpecificController;
			SpawnedTraitorPickers.Add(TraitorPicker);
		}
	}
}

