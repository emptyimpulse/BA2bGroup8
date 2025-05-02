// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JTCGameState.h"

#include "GameModes/LobbyGameModeBase.h"
#include "JumpingToConclusions/JumpingToConclusionsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/PuzzleSpawnManager.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JtCGameInstance.h"
#include "Subsystems/JtcPlayerStates.h"

AJTCGameState::AJTCGameState()
{
}

void AJTCGameState::PrintString(const FString& Str)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,Str);
	}
}


void AJTCGameState::OnRep_OnMatchStateChange()
{
}

void AJTCGameState::OnRep_OnVariableRepTest()
{
	PrintString(FString::Printf(TEXT("Server GameState %d"), VariableRepTest));
}
//----------------------------------------------------------------------------------------------------//
//---------------------------------------------Lobby--------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
void AJTCGameState::CheckAllPlayersReady()
{
	if(!HasAuthority()) return;

	for (APlayerState* PlayerState : PlayerArray)
	{
		AJtcPlayerStates* CustomPlayerState = Cast<AJtcPlayerStates>(PlayerState);
		if (!CustomPlayerState || !CustomPlayerState->IsReady())
		{
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,TEXT("Players Are not Ready Yet"));
			return;
		}
	}

	ALobbyGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALobbyGameModeBase>();
	if (GameMode && PlayerArray.Num() == 4)
	{
		//Game mode has to start game here
		GameMode->StartGame();
	}
}
//Debug Only
FString AJTCGameState::PrintAllPlayerNames()
{
	for (APlayerState* PlayerState : PlayerArray)
	{
		if (AJtcPlayerStates* CustomPlayerState = Cast<AJtcPlayerStates>(PlayerState))
		{
			PrintString(FString::Printf(TEXT("Player: %s"), *CustomPlayerState->GetPlayerNameCustom()));
			return *CustomPlayerState->GetPlayerNameCustom();
		}
		return "Null";
	}
	return "Null";
}
// Point apply System
//----------------------------------------------------------------------------------------------------//
//---------------------------------------------GAME---------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
void AJTCGameState::AddSolvedPuzzleScore(bool bWasSuccessfull)
{
	if(HasAuthority())
	{
		if(bWasSuccessfull)
		{
			SolvedPuzzles += 1;
			PrintString(FString::Printf(TEXT("CurrentScore: %d"), SolvedPuzzles));
		}
		else
		{
			FailedPuzzles += 1;
		}
		CheckIfAllPuzzlesSolved();
	}
}
// Games Win condition if all puzzles are solved
void AJTCGameState::CheckIfAllPuzzlesSolved()
{
	if (SolvedPuzzles == 3)
	{
		PrintString(FString::Printf(TEXT("Solvers Have Won With: %d"), SolvedPuzzles));
		RoundNumber += 1;
		AJumpingToConclusionsGameMode* CurrentGameMode = Cast<AJumpingToConclusionsGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode && RoundNumber <= 3)
		{
			CurrentGameMode->TeleportPlayersToSpawnLocations();
			APuzzleSpawnManager* PuzzleSpawnManager = Cast<APuzzleSpawnManager>(
				UGameplayStatics::GetActorOfClass(GetWorld(),APuzzleSpawnManager::StaticClass()));

			PuzzleSpawnManager->SpawnRandomPuzzles();
		}
		else
		{
			PrintString("Game End");
		}
	}
	else if (FailedPuzzles == 2)
	{
		PrintString(FString::Printf(TEXT("Traitors Have Won With: %d"), FailedPuzzles));
	}
}

// A Simple check to see if all players are ready on the lobby screen


// Replication Team dont worry about this
void AJTCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJTCGameState,OnMatchState)
	DOREPLIFETIME(AJTCGameState,VariableRepTest)
	DOREPLIFETIME(AJTCGameState,SolvedPuzzles)
	DOREPLIFETIME(AJTCGameState,FailedPuzzles)
}

