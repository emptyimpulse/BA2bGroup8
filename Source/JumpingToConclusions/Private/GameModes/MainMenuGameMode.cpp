// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuGameMode.h"

#include "Subsystems/JtCGameInstance.h"

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	
	UJtCGameInstance* GI = Cast<UJtCGameInstance>(GetGameInstance());
	if (GI)
	{
		FString TempName = TEXT("Null"); 
		GI->SetPlayerName(NewPlayer->GetUniqueID(), TempName);
	}
	
}
