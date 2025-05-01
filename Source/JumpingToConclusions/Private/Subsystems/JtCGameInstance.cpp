// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JtCGameInstance.h"

void UJtCGameInstance::SetPlayerName(const int32 PlayerUniqueID, const FString& PlayerName)
{

	PlayerNames.Add(PlayerUniqueID, PlayerName);
	GEngine->AddOnScreenDebugMessage(-1,25.0f,FColor::Red,FString::Printf(TEXT("Player Name: %s"),*PlayerName));
	
}

FString UJtCGameInstance::GetPlayerName(const int32 PlayerUniqueID)
{
	const FString* FindPlayerName = PlayerNames.Find(PlayerUniqueID);
	return FindPlayerName ? *FindPlayerName : TEXT("Null");
}
