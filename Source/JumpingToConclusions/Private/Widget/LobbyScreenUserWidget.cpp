// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LobbyScreenUserWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "GameFramework/GameState.h"
#include "Subsystems/JtcPlayerStates.h"

void ULobbyScreenUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LobbyReadyButton)
	{
		LobbyReadyButton->OnClicked.AddDynamic(this,&ULobbyScreenUserWidget::OnReadyButtonClicked);
	}
	
}

void ULobbyScreenUserWidget::OnReadyButtonClicked()
{
	if(APlayerController* PC = GetOwningPlayer())
	{
		if (AJtcPlayerStates* CustomPlayerState = PC->GetPlayerState<AJtcPlayerStates>())
		{
			CustomPlayerState->ServerSetReady(true);
		}
	}
}

void ULobbyScreenUserWidget::RefreshPlayers()
{
	PlayerListVerticalBox->ClearChildren();

	AGameStateBase* GS = GetWorld()->GetGameState();

	if (!GS) return;

	for (APlayerState* PS : GS->PlayerArray)
	{
		AJtcPlayerStates* CustomPlayerState = Cast<AJtcPlayerStates>(PS);
		if (CustomPlayerState)
		{
			ULobbyPlayeWidget* NewPlayerWidget = CreateWidget<ULobbyPlayeWidget>(this,LobbyPlayerEntryClass);
			PlayerListVerticalBox->AddChild(NewPlayerWidget);
			NewPlayerWidget->SetupWithPlayerState(CustomPlayerState);
		}
	}
}

