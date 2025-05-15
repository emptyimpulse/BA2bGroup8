// Fill out your copyright notice in the Description page of Project Settings.


#include "JtcPlayerController.h"

#include "JumpingToConclusions/JumpingToConclusionsCharacter.h"
#include "Subsystems/JtCGameInstance.h"
#include "Widget/Endofgamewidget.h"

void AJtcPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
void AJtcPlayerController::Server_SetPlayerName_Implementation(const FString& Name)
{
	UJtCGameInstance* CustomGameInstance = Cast<UJtCGameInstance>(GetGameInstance());
	if (CustomGameInstance)
	{
		CustomGameInstance->SetPlayerName(GetUniqueID(), Name);
	}
}

void AJtcPlayerController::ShowEndGameWidget()
{
	if (EndOfGameWidgetClass)
	{
		EndOfGameWidget = CreateWidget<UEndofgamewidget>(this,EndOfGameWidgetClass);
		if (EndOfGameWidget)
		{
			EndOfGameWidget->AddToViewport();
		}
	}
}



