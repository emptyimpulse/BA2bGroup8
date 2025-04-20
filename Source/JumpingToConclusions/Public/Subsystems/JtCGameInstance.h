// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JtCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API UJtCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString PlayerName;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString NewPlayerName);
	FORCEINLINE FString GetPlayerName() { return PlayerName;}
};
