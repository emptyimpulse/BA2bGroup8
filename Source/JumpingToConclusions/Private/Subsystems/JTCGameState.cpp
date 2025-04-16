// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JTCGameState.h"

#include "Net/UnrealNetwork.h"

AJTCGameState::AJTCGameState()
{
}

void AJTCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJTCGameState,OnMatchState)
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

