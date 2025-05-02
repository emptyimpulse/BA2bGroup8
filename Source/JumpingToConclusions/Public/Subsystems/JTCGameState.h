// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/MatchStateEnums.h"
#include "JumpingToConclusions/JumpingToConclusionsCharacter.h"
#include "JTCGameState.generated.h"

class AJtcPlayerStates;
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
	
	UFUNCTION()
	void OnRep_OnMatchStateChange();
	
	UFUNCTION()
	void OnRep_OnVariableRepTest();

	UFUNCTION(BlueprintCallable,Category="Game Score")
	void AddSolvedPuzzleScore(bool bWasSuccessfull);

	UFUNCTION(BlueprintCallable,Category="Player Data")
	FString PrintAllPlayerNames();
	
	void CheckIfAllPuzzlesSolved();

	void CheckAllPlayersReady();

	UPROPERTY(ReplicatedUsing  = OnRep_OnMatchStateChange)
	EMatchState OnMatchState = EMatchState::BeginMatch;
protected:
	
	UPROPERTY(ReplicatedUsing = OnRep_OnVariableRepTest ,BlueprintReadOnly)
	int VariableRepTest;

	UPROPERTY(Replicated,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 SolvedPuzzles = 0;
	
	UPROPERTY(Replicated,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 FailedPuzzles = 0;

	UPROPERTY(Replicated,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 RoundNumber = 0;
	
};
