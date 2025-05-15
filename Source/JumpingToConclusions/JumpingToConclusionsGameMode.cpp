// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingToConclusionsGameMode.h"

#include "JtcPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ObserverGuessingCube.h"
#include "Managers/PuzzleSpawnManager.h"
#include "Net/UnrealNetwork.h"
#include "ProductionTools/SetSpawnPoint.h"
#include "Subsystems/JTCGameState.h"
#include "Subsystems/JtcPlayerStates.h"
#include "UObject/ConstructorHelpers.h"

AJumpingToConclusionsGameMode::AJumpingToConclusionsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/JumpingToConclusions/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerStateClass = AJtcPlayerStates::StaticClass();
}


void AJumpingToConclusionsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(NewPlayer);

	NumberOfPlayersLoggedIn++;

	if (NumberOfPlayersLoggedIn == 4)
	{
		ShuffleAllPlayers();
	}
}


void AJumpingToConclusionsGameMode::ShuffleAllPlayers()
{
	int64 DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	FRandomStream SRand = FRandomStream();
	SRand.Initialize(DateInSeconds);
	for (int32 i = PlayerControllerList.Num() - 1; i > 0; i--)
	{
		int32 j = SRand.FRandRange(0, PlayerControllerList.Num() - 1);
		APlayerController* temp = PlayerControllerList[i];
		PlayerControllerList[i] = PlayerControllerList[j];
		PlayerControllerList[j] = temp;
	}
	TestShuffle();

	if (bAreTeamsAssigned)
	{
		TraitorList[0] = PlayerControllerList[0];
		ObserverList[0] = PlayerControllerList[1];
		SolverList[0] = PlayerControllerList[2];
		SolverList[1] = PlayerControllerList[3];
	}
	else
	{
		TraitorList.Add(PlayerControllerList[0]);
		ObserverList.Add(PlayerControllerList[1]);
		SolverList.Add(PlayerControllerList[2]);
		SolverList.Add(PlayerControllerList[3]);

		bAreTeamsAssigned = true;
	}
	//spawning necessary game components
	APuzzleSpawnManager* PuzzleSpawnManager = Cast<APuzzleSpawnManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), APuzzleSpawnManager::StaticClass()));
	PuzzleSpawnManager->SpawnRandomPuzzles();

	AJTCGameState* CustomGameState = GetGameState<AJTCGameState>();
	CustomGameState->CreatePuzzleAnswers();
	GetPlayersForObserverCube();

	AObserverGuessingCube* ObserverSpawnManager = Cast<AObserverGuessingCube>(
	UGameplayStatics::GetActorOfClass(GetWorld(), AObserverGuessingCube::StaticClass()));
	ObserverSpawnManager->SpawnObserverTraitorPickers();
	//Player Management
	TeleportPlayersToSpawnLocations();

	AJumpingToConclusionsCharacter* CustomPC = Cast<AJumpingToConclusionsCharacter>(TraitorList[0]->GetPawn());
	if (CustomPC)
	{
		CustomPC->ShowTraitorDisplay();
	}
}

void AJumpingToConclusionsGameMode::TestShuffle()
{
	for (int i = PlayerControllerList.Num() - 1; i >= 0; i--)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
		                                 FString::Printf(
			                                 TEXT("CurrentGameController %s"), *PlayerControllerList[i]->GetName()));
	}
}



void AJumpingToConclusionsGameMode::TeleportPlayersToSpawnLocations()
{
	ASetSpawnPoint* SpawnPoint = Cast<ASetSpawnPoint>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ASetSpawnPoint::StaticClass()));

	if (APawn* TraitorPawn = TraitorList[0]->GetPawn())
	{
		TraitorPawn->SetActorLocation(SpawnPoint->GetTraitorSpawnPointLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Traitor Player Not Found"));
	}

	if (APawn* ObserverPawn = ObserverList[0]->GetPawn())
	{
		ObserverPawn->SetActorLocation(SpawnPoint->GetObserverSpawnPointLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Observer Player Not Found"));
	}

	for (int32 i = SolverList.Num() - 1; i >= 0; i--)
	{
		if (APawn* SolverPawn = SolverList[i]->GetPawn())
		{
			SolverPawn->SetActorLocation(SpawnPoint->GetSolverSpawnPointLocation());
		}
	}
}

void AJumpingToConclusionsGameMode::CheckIfTraitorCorrect(APlayerState* ChosenPlayerController)
{
	AJTCGameState* GS = GetWorld()->GetGameState<AJTCGameState>();
	if (TraitorList[0] == ChosenPlayerController->GetPlayerController())
	{
		//TODO Show endgame screen if Won
		if (GS)
		{
			GS->NetMuticastEndGame();
		}
	}
	else
	{
		if (GS)
		{
			GS->NetMuticastEndGame();
		}
	}
}

void AJumpingToConclusionsGameMode::GetPlayersForObserverCube()
{
	if (HasAuthority())
	{
		const AJumpingToConclusionsGameMode* CurrentGameMode = Cast<AJumpingToConclusionsGameMode>(
			GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			PuzzlersControllers.Add(CurrentGameMode->TraitorList[0]->GetPlayerState<APlayerState>());
			PuzzlersControllers.Add(CurrentGameMode->SolverList[0]->GetPlayerState<APlayerState>());
			PuzzlersControllers.Add(CurrentGameMode->SolverList[1]->GetPlayerState<APlayerState>());
		}
	}
}

void AJumpingToConclusionsGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJumpingToConclusionsGameMode,PlayerControllerList);
}
