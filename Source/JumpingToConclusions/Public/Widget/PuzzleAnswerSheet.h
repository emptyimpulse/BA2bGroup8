// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "PuzzleAnswerSheet.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API UPuzzleAnswerSheet : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 AnswerIndex;
	
protected:
	UPROPERTY()
	UTextBlock* AnswerText;
	
	UPROPERTY(BlueprintReadOnly,Meta = (BindWidget))
	UEditableText* AnswerTextBox;

	UPROPERTY(Meta = (BindWidget))
	UButton* AnswerButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION(BlueprintCallable)
	void OnAnswerButtonClicked(int32 SubmittedAnswer);
	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClicked();
	virtual void NativeConstruct() override;
};
