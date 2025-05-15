// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JumpingToConclusionsGameMode.generated.h"

class ASetSpawnPoint;

UCLASS(minimalapi)
class AJumpingToConclusionsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJumpingToConclusionsGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	void TestShuffle();

	UFUNCTION(BlueprintCallable)
	void TeleportPlayersToSpawnLocations();

	void CheckIfTraitorCorrect(APlayerState* ChosenPlayerController);

	void GetPlayersForObserverCube();
	//--------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------PROPERTIES--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//

	//Inital List Of Joint Players
	UPROPERTY(Replicated,BlueprintReadOnly)
	TArray<APlayerController*> PlayerControllerList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> ObserverList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> SolverList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> TraitorList;
	
	TArray<APlayerState*> PuzzlersControllers;
	
	UPROPERTY()
	int8 SolvedPuzzles = 0;
	bool bAreTeamsAssigned = false;

	UPROPERTY(EditAnywhere)
	ASetSpawnPoint* SpawnPoints;
protected:
	UFUNCTION()
	void ShuffleAllPlayers();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	int8 NumberOfPlayersLoggedIn = 0;
};



