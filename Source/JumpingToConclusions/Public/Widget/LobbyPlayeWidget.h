// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Subsystems/JtcPlayerStates.h"
#include "LobbyPlayeWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API ULobbyPlayeWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetupWithPlayerState(AJtcPlayerStates* PlayerState);

	protected:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* PlayerNameText;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ReadyStatusText;
};
