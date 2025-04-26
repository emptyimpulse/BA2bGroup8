// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LobbyGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AllPlayers.AddUnique(NewPlayer);
}

