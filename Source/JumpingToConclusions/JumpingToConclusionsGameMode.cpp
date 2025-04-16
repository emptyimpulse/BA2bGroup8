// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingToConclusionsGameMode.h"
#include "JumpingToConclusionsCharacter.h"
#include "Subsystems/JTCGameState.h"
#include "UObject/ConstructorHelpers.h"

AJumpingToConclusionsGameMode::AJumpingToConclusionsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/JumpingToConclusions/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AJumpingToConclusionsGameMode::SwapMatchState()
{
	if(AJTCGameState* GS = GetGameState<AJTCGameState>())
	{
		if(GS->OnMatchState == EMatchState::BeginMatch)
		{
			GS->OnMatchState = EMatchState::PreLobby;
			GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,"Lobby");
		}
		else
		{
			GS->OnMatchState = EMatchState::BeginMatch;
			GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,"BeginMatch");
		}
	}
}
