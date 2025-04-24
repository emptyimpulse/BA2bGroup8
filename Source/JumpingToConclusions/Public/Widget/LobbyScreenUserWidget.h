// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayeWidget.h"
#include "Blueprint/UserWidget.h"
#include "LobbyScreenUserWidget.generated.h"

class UVerticalBox;
class UButton;
/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API ULobbyScreenUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* LobbyReadyButton;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerListVerticalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
	TSubclassOf<ULobbyPlayeWidget> LobbyPlayerEntryClass;

	UFUNCTION()
	void OnReadyButtonClicked();

	UFUNCTION(BlueprintCallable)
	void RefreshPlayers();

};
