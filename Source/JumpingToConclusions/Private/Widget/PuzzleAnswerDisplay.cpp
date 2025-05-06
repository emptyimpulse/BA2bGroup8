// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PuzzleAnswerDisplay.h"

#include "JtcPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JTCGameState.h"


void UPuzzleAnswerDisplay::NativeConstruct()
{
	//this is so scuffed
	Super::NativeConstruct();
	AJTCGameState* CustomGameState = GetWorld()->GetGameStateChecked<AJTCGameState>();
	int32 AnswerFromSheet = CustomGameState->AnswerSheet[AnswerIndex];
	AnswerText->SetText(FText::Format(FText::FromString("Answer For Index: {0} is {1}"),AnswerIndex,AnswerFromSheet));
}



void UPuzzleAnswerDisplay::OnQuitButtonClicked()
{
	AJtcPlayerController* CustomPlayerController = Cast<AJtcPlayerController>(GetOwningPlayer());
	if (CustomPlayerController)
	{
		CustomPlayerController->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		CustomPlayerController->SetInputMode(InputMode);
		this->RemoveFromParent();
	}
}
void UPuzzleAnswerDisplay::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPuzzleAnswerDisplay, AnswerIndex);
}
