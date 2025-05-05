// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PuzzleAnswerSheet.h"

#include "Subsystems/JTCGameState.h"

void UPuzzleAnswerSheet::OnAnswerButtonClicked_Implementation(int32 SubmittedAnswer)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	FString::Printf(TEXT("AnswerInput %d"), SubmittedAnswer));
	if (AJTCGameState* CustomGameState = Cast<AJTCGameState>(GetWorld()->GetGameState()))
	{
		if (CustomGameState->AnswerSheet[AnswerIndex] == SubmittedAnswer)
		{
			CustomGameState->AddSolvedPuzzleScore(true);
			this->RemoveFromParent();
		}
		else
		{
			CustomGameState->AddSolvedPuzzleScore(false);
			this->RemoveFromParent();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed Cast to gamestate");
	}
}

void UPuzzleAnswerSheet::NativeConstruct()
{
	Super::NativeConstruct();

	AnswerTextBox->SetHintText(FText::Format(FText::FromString("Answer text:{0}"),AnswerIndex));
}


