// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/MatchStateEnums.h"
#include "JumpingToConclusionsGameMode.generated.h"

UCLASS(minimalapi)
class AJumpingToConclusionsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJumpingToConclusionsGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	void SwapMatchState();

	void TestShuffle();
	
	virtual void PostInitializeComponents() override;
	//--------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------PROPERTIES--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//

	//Inital List Of Joint Players
	UPROPERTY()
	TArray<APlayerController*> PlayerControllerList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> ObserverList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> SolverList;
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> TraitorList;
	
	UPROPERTY()
	int8 SolvedPuzzles = 0;

	bool bAreTeamsAssigned = false;
};



