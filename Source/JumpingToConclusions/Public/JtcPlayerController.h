// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JtcPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API AJtcPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Server, Reliable)
	void Server_SetPlayerName(const FString& Name);

	

protected:
	virtual void BeginPlay() override;

public:
	void ShowEndGameWidget();

	
	
};
