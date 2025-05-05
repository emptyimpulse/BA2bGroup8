// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PuzzleAnswerSheet.h"

#include "Subsystems/JTCGameState.h"

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
}

void UPuzzleAnswerSheet::NativeConstruct()
{
	Super::NativeConstruct();

	AnswerTextBox->SetHintText(FText::Format(FText::FromString("Answer text:{0}"),AnswerIndex));
}


