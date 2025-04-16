// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/MatchStateEnums.h"
#include "JTCGameState.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API AJTCGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	
	AJTCGameState();
	
	void PrintString( const FString& Str );

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing  = OnRep_OnMatchStateChange)
	EMatchState OnMatchState = EMatchState::BeginMatch;

	UFUNCTION(BlueprintCallable)
	void OnRep_OnMatchStateChange();
	
};
