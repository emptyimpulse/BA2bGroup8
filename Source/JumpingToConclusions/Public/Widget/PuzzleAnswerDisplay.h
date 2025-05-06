// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PuzzleAnswerDisplay.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API UPuzzleAnswerDisplay : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated);
	int32 AnswerIndex;
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AnswerText;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClicked();
	virtual void NativeConstruct() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
