// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JtCGameInstance.h"

void UJtCGameInstance::SetPlayerName(FString NewPlayerName)
{
	PlayerName = NewPlayerName;
	GEngine->AddOnScreenDebugMessage(-1,25.0f,FColor::Red,FString::Printf(TEXT("Player Name: %s"),*PlayerName));
}
