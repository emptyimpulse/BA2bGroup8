// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JTCGameState.h"

#include "JtcPlayerController.h"
#include "GameModes/LobbyGameModeBase.h"
#include "JumpingToConclusions/JumpingToConclusionsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/PuzzleSpawnManager.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JtcPlayerStates.h"
#include "World/PointDisplayActor.h"

AJTCGameState::AJTCGameState()
{
	AnswerSheet.Add(0);
	AnswerSheet.Add(0);
	AnswerSheet.Add(0);
}

void AJTCGameState::BeginPlay()
{
	Super::BeginPlay();
	DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	SRand = FRandomStream();
	SRand.Initialize(DateInSeconds);
}

void AJTCGameState::PrintString(const FString& Str)
{
	if (GEngine)
	{
		
	}
}


void AJTCGameState::OnRep_OnMatchStateChange()
{
}

void AJTCGameState::OnRep_OnVariableRepTest()
{
	PrintString(FString::Printf(TEXT("Server GameState %d"), VariableRepTest));
}

void AJTCGameState::NetMuticastEndGame_Implementation()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* IteraionPC= Iterator->Get();
		if (IteraionPC && IteraionPC->IsLocalController())
		{
			if (AJtcPlayerController* CustomPC = Cast<AJtcPlayerController>(IteraionPC) )
			{
				
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------//
//---------------------------------------------Lobby--------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
void AJTCGameState::CheckAllPlayersReady()
{
	if (!HasAuthority()) return;

	for (APlayerState* PlayerState : PlayerArray)
	{
		AJtcPlayerStates* CustomPlayerState = Cast<AJtcPlayerStates>(PlayerState);
		if (!CustomPlayerState || !CustomPlayerState->IsReady())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan,
			                                 TEXT("Players Are not Ready Yet"));
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


void AJTCGameState::OnRep_OnPuzzleControllersChange()
{
}


void AJTCGameState::OnRep_OnPointChange()
{
	APointDisplayActor* PointDisplay = Cast<APointDisplayActor>(
	UGameplayStatics::GetActorOfClass(GetWorld(), APointDisplayActor::StaticClass()));

	PointDisplay->UpdateScoreOnDisplay();
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
	if (HasAuthority())
	{
		if (bWasSuccessfull)
		{
			TotalPuzzles++;
			SolvedPuzzles += 1;
			OnRep_OnPointChange();
		}
		else
		{
			TotalPuzzles++;
			FailedPuzzles += 1;
			OnRep_OnPointChange();
		}
		CheckIfAllPuzzlesSolved();
	}
}

// Games Win condition if all puzzles are solved
void AJTCGameState::CheckIfAllPuzzlesSolved()
{
	if (HasAuthority())
	{
		if (TotalPuzzles == 3)
		{
			if (SolvedPuzzles == 2)
			{
				PrintString(FString::Printf(TEXT("Solvers Have Won With: %d"), SolvedPuzzles));
				SolvedPuzzles = 0;
				RoundNumber += 1;
				AJumpingToConclusionsGameMode* CurrentGameMode = Cast<AJumpingToConclusionsGameMode>(
					GetWorld()->GetAuthGameMode());
				if (CurrentGameMode && RoundNumber <= 3)
				{
					//CurrentGameMode->TeleportPlayersToSpawnLocations();
					APuzzleSpawnManager* PuzzleSpawnManager = Cast<APuzzleSpawnManager>(
						UGameplayStatics::GetActorOfClass(GetWorld(), APuzzleSpawnManager::StaticClass()));
					PuzzleSpawnManager->SpawnRandomPuzzles();
					CreatePuzzleAnswers();
				}
				else
				{
					//TODO adjust this when hazel gives End Game widget
					PrintString("Game End");
				}
			}
			else
			{
				PrintString(FString::Printf(TEXT("Traitors Have Won With: %d"), FailedPuzzles));
				AJumpingToConclusionsGameMode* CurrentGameMode = Cast<AJumpingToConclusionsGameMode>(
					GetWorld()->GetAuthGameMode());
				if (CurrentGameMode && RoundNumber <= 3)
				{
					//CurrentGameMode->TeleportPlayersToSpawnLocations();
					APuzzleSpawnManager* PuzzleSpawnManager = Cast<APuzzleSpawnManager>(
						UGameplayStatics::GetActorOfClass(GetWorld(), APuzzleSpawnManager::StaticClass()));
					PuzzleSpawnManager->SpawnRandomPuzzles();
					CreatePuzzleAnswers();
				}
				else
				{
					PrintString("Game End");
				}
			}
		}
	}
}

// A Simple check to see if all players are ready on the lobby screen

void AJTCGameState::CreatePuzzleAnswers()
{
	if (HasAuthority())
	{
		for (int8 i = 0; i <= 2; i++)
		{
			int32 RandomGeneratedAnswer = SRand.RandRange(111111, 999999);

			AnswerSheet[i] = RandomGeneratedAnswer;
		}
	}
}


// Replication Team dont worry about this
void AJTCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJTCGameState, OnMatchState)
	DOREPLIFETIME(AJTCGameState, VariableRepTest)
	DOREPLIFETIME(AJTCGameState, SolvedPuzzles)
	DOREPLIFETIME(AJTCGameState, FailedPuzzles)
	DOREPLIFETIME(AJTCGameState, AnswerSheet)
	DOREPLIFETIME(AJTCGameState, PuzzlersControllers)
	DOREPLIFETIME(AJTCGameState, PuzzlersAdded)
}
