// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingToConclusionsGameMode.h"
#include "JumpingToConclusionsCharacter.h"
#include "Subsystems/JTCGameState.h"
#include "Subsystems/JtcPlayerStates.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

AJumpingToConclusionsGameMode::AJumpingToConclusionsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/JumpingToConclusions/Blueprints/BP_ThirdPersonCharacter"));
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
	
}

void AJumpingToConclusionsGameMode::SwapMatchState()
{
	if(AJTCGameState* GS = GetGameState<AJTCGameState>())
	{
		if(GS->OnMatchState == EMatchState::BeginMatch)
		{
			GS->OnMatchState = EMatchState::PreLobby;
		}
		else
		{
			GS->OnMatchState = EMatchState::BeginMatch;
		}
		
		switch (GS->OnMatchState) {
		case EMatchState::PreLobby:
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"PreLobby");
			break;
			
		case EMatchState::BeginMatch:
			{
				int64 DateInSeconds = FDateTime::Now().ToUnixTimestamp();
				FRandomStream SRand = FRandomStream();
				SRand.Initialize(DateInSeconds);
				for (int32 i = PlayerControllerList.Num() - 1; i > 0; i--)
				{
					int32 j = SRand.FRandRange(0,PlayerControllerList.Num()-1);
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
			}
			break;
		case EMatchState::EndMatch:
			break;
		}
	}
}

void AJumpingToConclusionsGameMode::TestShuffle()
{
	for(int i = PlayerControllerList.Num() - 1; i >= 0; i--)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,
		FString::Printf(TEXT("CurrentGameController %s"), *PlayerControllerList[i]->GetName()));
	}
}






