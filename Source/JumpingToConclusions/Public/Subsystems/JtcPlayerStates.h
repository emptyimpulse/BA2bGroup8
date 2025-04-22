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
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual FString GetPlayerNameCustom() const override;

	void SetCustomPlayerName(FString CustomPlayerName);

	UPROPERTY(EditAnywhere)
	FString PlayerName;
private:
	
};
