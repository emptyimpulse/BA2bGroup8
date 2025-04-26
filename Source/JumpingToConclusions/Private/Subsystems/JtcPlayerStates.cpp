// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JtcPlayerStates.h"

#include "JtcPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JtCGameInstance.h"
#include "Subsystems/JTCGameState.h"


void AJtcPlayerStates::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AJtcPlayerController* CustomPlayerController = Cast<AJtcPlayerController>(GetPlayerController());
	if (CustomPlayerController)
	{
		CustomPlayerController->Server_SetPlayerName(PlayerName);
	}
}


void AJtcPlayerStates::ServerSetReady_Implementation(bool bReady)
{
	bIsReady = bReady;
}

void AJtcPlayerStates::SetCustomPlayerName_Implementation(const FString& CustomPlayerName)
{
	PlayerName = CustomPlayerName;
}

void AJtcPlayerStates::OnRep_Ready()
{
	if (AJTCGameState* CustomGameState = Cast<AJTCGameState>(GetWorld()->GetGameState()))
	{
		CustomGameState->CheckAllPlayersReady();
	}
}
void AJtcPlayerStates::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJtcPlayerStates, bIsReady);
	DOREPLIFETIME(AJtcPlayerStates, PlayerName);
}
