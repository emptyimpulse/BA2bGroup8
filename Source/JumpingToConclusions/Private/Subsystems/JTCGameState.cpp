// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JTCGameState.h"

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
	if(HasAuthority())
	{
		PrintString("Server GameState");
	}
	else
	{
		PrintString("Client GameState");
	}
}

void AJTCGameState::OnRep_OnVariableRepTest()
{
	PrintString(FString::Printf(TEXT("Server GameState %d"), VariableRepTest));
}

void AJTCGameState::AddSolvedPuzzleScore(bool bWasSuccessfull)
{
	if(HasAuthority())
	{
		if(bWasSuccessfull)
		{
			SolvedPuzzles += 1;
		}
		else
		{
			FailedPuzzles += 1;
		}
		CheckIfAllPuzzlesSolved();
	}
}

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


void AJTCGameState::CheckIfAllPuzzlesSolved()
{
	if (SolvedPuzzles == 4)
	{
		PrintString(FString::Printf(TEXT("Solvers Have Won With: %d"), SolvedPuzzles));
	}
	else if (FailedPuzzles == 2)
	{
		PrintString(FString::Printf(TEXT("Traitors Have Won With: %d"), FailedPuzzles));
	}
	
}


void AJTCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJTCGameState,OnMatchState)
	DOREPLIFETIME(AJTCGameState,VariableRepTest)
	DOREPLIFETIME(AJTCGameState,SolvedPuzzles)
	DOREPLIFETIME(AJTCGameState,FailedPuzzles)
}

