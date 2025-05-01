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
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, FString> PlayerNames;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const int32 PlayerUniqueID, const FString& PlayerName);
	FORCEINLINE FString GetPlayerName(const int32 PlayerUniqueID);
};
