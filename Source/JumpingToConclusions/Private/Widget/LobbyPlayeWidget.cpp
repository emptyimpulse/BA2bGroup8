// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LobbyPlayeWidget.h"

void ULobbyPlayeWidget::SetupWithPlayerState(AJtcPlayerStates* PlayerState)
{
	if (PlayerState)
	{
		PlayerNameText->SetText(FText::FromString(PlayerState->PlayerName));
		ReadyStatusText->SetText(PlayerState->IsReady() ? FText::FromString("Ready") : FText::FromString("Not Ready"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"PlayerState Doesnt exist");
	}

}
