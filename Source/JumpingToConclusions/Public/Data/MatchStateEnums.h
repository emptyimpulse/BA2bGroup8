// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchStateEnums.generated.h"

UENUM()
enum class EMatchState : uint8
{
	PreLobby UMETA(DisplayName = "PreLobby"),
	BeginMatch UMETA(DisplayName = "BeginMatch"),
	EndMatch UMETA(DisplayName = "EndMatch"),

	//add any matchs tates to this as needed in the same style as above
	
};