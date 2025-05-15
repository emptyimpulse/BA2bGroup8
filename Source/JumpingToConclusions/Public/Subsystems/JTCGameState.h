// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/MatchStateEnums.h"
#include "Widget/Endofgamewidget.h"
#include "JTCGameState.generated.h"

class AJtcPlayerStates;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FObserverCubeDelegate);
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

	UFUNCTION(NetMulticast, reliable)
	void NetMuticastEndGame();

	UFUNCTION(BlueprintCallable,Category="Game Score")
	void AddSolvedPuzzleScore(bool bWasSuccessfull);

	UFUNCTION(BlueprintCallable,Category="Player Data")
	FString PrintAllPlayerNames();
	
	
	void CheckIfAllPuzzlesSolved();

	void CheckAllPlayersReady();

	UFUNCTION()
	void OnRep_OnPointChange();
	
	UPROPERTY(ReplicatedUsing  = OnRep_OnMatchStateChange)
	EMatchState OnMatchState = EMatchState::BeginMatch;
	
	FRandomStream SRand;

	UPROPERTY(Replicated,BlueprintReadOnly)
	TArray<int32> AnswerSheet;

	void CreatePuzzleAnswers();

	UFUNCTION()
	void OnRep_OnPuzzleControllersChange();

	UPROPERTY(Replicated)
	TArray<APlayerState*> PuzzlersControllers;
	
	FObserverCubeDelegate OnObserverDelegate;
	
	UPROPERTY(ReplicatedUsing = OnRep_OnPuzzleControllersChange,BlueprintReadOnly)
	int32 PuzzlersAdded = 0;
	
	UPROPERTY(ReplicatedUsing= OnRep_OnPointChange,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 SolvedPuzzles = 0;
	
	UPROPERTY(ReplicatedUsing= OnRep_OnPointChange,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 FailedPuzzles = 0;
	
protected: 

	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_OnVariableRepTest ,BlueprintReadOnly)
	int VariableRepTest;
	
	UPROPERTY(Replicated,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 TotalPuzzles = 0;

	UPROPERTY(Replicated,BlueprintReadOnly,VisibleAnywhere,Category="Game Score")
	int32 RoundNumber = 0;

	
	int64 DateInSeconds;
};


