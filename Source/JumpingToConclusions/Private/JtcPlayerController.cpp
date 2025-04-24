// Fill out your copyright notice in the Description page of Project Settings.


#include "JtcPlayerController.h"

#include "Subsystems/JtCGameInstance.h"

void AJtcPlayerController::Server_SetPlayerName_Implementation(const FString& Name)
{
	UJtCGameInstance* CustomGameInstance = Cast<UJtCGameInstance>(GetGameInstance());
	if (CustomGameInstance)
	{
		CustomGameInstance->SetPlayerName(CustomGameInstance->GetUniqueID(), Name);
	}
}
