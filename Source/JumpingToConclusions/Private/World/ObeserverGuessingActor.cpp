// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ObeserverGuessingActor.h"

#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JTCGameState.h"

AObeserverGuessingActor::AObeserverGuessingActor()
{
	PlayerNameDisplay= CreateDefaultSubobject<UTextBlock>(TEXT("TextBlock"));
}

void AObeserverGuessingActor::BeginPlay()
{
	Super::BeginPlay();
	AJTCGameState* CustomGameState = GetWorld()->GetGameStateChecked<AJTCGameState>();
	ChosenPlayerController = CustomGameState->PuzzlersControllers[PlayerIndex];
	PlayerNameDisplay->SetText(FText::FromString(
		"Player: "+ ChosenPlayerController->GetName()));
}
void AObeserverGuessingActor::Interact_Implementation(AJumpingToConclusionsCharacter* InstigatingPlayer)
{
	
}

void AObeserverGuessingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AObeserverGuessingActor,PlayerIndex);
}

