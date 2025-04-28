// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LobbyGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AllPlayers.AddUnique(NewPlayer);
}

void ALobbyGameModeBase::StartGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,TEXT("World Travel"));

		World->ServerTravel("/Game/JumpingToConclusions/Maps/GameLevel?Listen");
	}
}

