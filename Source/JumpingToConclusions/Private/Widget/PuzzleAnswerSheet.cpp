// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PuzzleAnswerSheet.h"

#include "JtcPlayerController.h"
#include "Subsystems/JTCGameState.h"

void UPuzzleAnswerSheet::NativeConstruct()
{
	Super::NativeConstruct();

	AnswerTextBox->SetHintText(FText::Format(FText::FromString("Answer text:{0}"),AnswerIndex));
}
void UPuzzleAnswerSheet::OnAnswerButtonClicked(int32 SubmittedAnswer)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	FString::Printf(TEXT("AnswerInput %d"), SubmittedAnswer));
	if (AJumpingToConclusionsCharacter* CustomCharacter = Cast<AJumpingToConclusionsCharacter>(GetOwningPlayerPawn()))
	{
		CustomCharacter->ServerAnswerToPuzzle(SubmittedAnswer,AnswerIndex);
		this->RemoveFromParent();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed Cast to Character");
	}
	AJtcPlayerController* CustomPlayerController = Cast<AJtcPlayerController>(GetOwningPlayer());
	if (CustomPlayerController)
	{
		CustomPlayerController->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		CustomPlayerController->SetInputMode(InputMode);
		this->RemoveFromParent();
	}
}



