// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LobbyPlayeWidget.h"

#include "JtcPlayerController.h"
#include "Subsystems/JtCGameInstance.h"

void ULobbyPlayeWidget::SetupWithPlayerState(AJtcPlayerStates* PlayerState)
{

	//This is just a Nested hell and im sorry
	if (PlayerState)
	{
		if (AJtcPlayerController* CustomPlayerController = Cast<AJtcPlayerController>(PlayerState->GetPlayerController()))
		{
			if (UJtCGameInstance* CustomGameInstance = Cast<UJtCGameInstance>(GetGameInstance()))
			{
				PlayerNameText->SetText(FText::FromString(*CustomGameInstance->GetPlayerName(CustomPlayerController->GetUniqueID())));
				ReadyStatusText->SetText(PlayerState->IsReady() ? FText::FromString("Ready") : FText::FromString("Not Ready"));
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"PlayerState Doesnt exist");
	}

}
