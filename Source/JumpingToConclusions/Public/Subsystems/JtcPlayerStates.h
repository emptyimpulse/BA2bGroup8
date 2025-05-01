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

	bool IsReady() const {return bIsReady;}
	
	
	FString GetCustomPlayerName() const {return PlayerName;}

	UFUNCTION(Server, Reliable)
	void SetCustomPlayerName(const FString& CustomPlayerName);
	
	UPROPERTY(ReplicatedUsing=OnRep_Ready)
	bool bIsReady = false;

	UPROPERTY(Replicated)
	FString PlayerName;
	
	UFUNCTION(Server, Reliable)
	void ServerSetReady(bool bReady);

	UFUNCTION()
	void OnRep_Ready();
private:
	
};
