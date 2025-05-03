// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/PuzzleTempCube.h"
#include "PuzzleSpawnManager.generated.h"

UCLASS()
class JUMPINGTOCONCLUSIONS_API APuzzleSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int64 DateInSeconds;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//----------------------------------------------------------------------------------------------------//
	//-------------------------------------------PROPERTIES-----------------------------------------------//
	//----------------------------------------------------------------------------------------------------//

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<APuzzleTempCube>> SpawnedActors;

	UPROPERTY()
	TArray<APuzzleTempCube*> SpawnedPuzzles;
	
	TArray<USceneComponent*> SpawnLocations;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointOne;
	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointTwo;
	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointThree;

	FRandomStream SRand;

	//----------------------------------------------------------------------------------------------------//
	//--------------------------------------------FUNCTIONS-----------------------------------------------//
	//----------------------------------------------------------------------------------------------------//

	void SpawnRandomPuzzles();
};
