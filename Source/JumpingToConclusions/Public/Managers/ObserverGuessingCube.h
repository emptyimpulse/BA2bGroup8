// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObserverGuessingCube.generated.h"

class AObeserverGuessingActor;

UCLASS()
class JUMPINGTOCONCLUSIONS_API AObserverGuessingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObserverGuessingCube();

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AObeserverGuessingActor> ObeserverGuessingActorClass;
	
	UPROPERTY()
	TArray<AObeserverGuessingActor*> SpawnedTraitorPickers;
	
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

	void SpawnObserverTraitorPickers();

};
