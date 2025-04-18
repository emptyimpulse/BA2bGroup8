// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JtcPlayerStates.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API AJtcPlayerStates : public APlayerState
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void GetPlayerNames(FString PlayerNameInput);
private:
	UPROPERTY(EditAnywhere)
	FString PlayerName;
};
