// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingToConclusionsGameMode.h"
#include "JumpingToConclusionsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJumpingToConclusionsGameMode::AJumpingToConclusionsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/JumpingToConclusions/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
