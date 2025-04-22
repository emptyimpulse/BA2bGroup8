// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JtcPlayerStates.h"

#include "Net/UnrealNetwork.h"
#include "Subsystems/JtCGameInstance.h"


void AJtcPlayerStates::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UGameInstance* GameInstance = GetGameInstance();
	if (UJtCGameInstance* CustomGameInstance = Cast<UJtCGameInstance>(GameInstance))
	{
		SetCustomPlayerName(CustomGameInstance->GetPlayerName());
		GEngine->AddOnScreenDebugMessage(-1,25.0f,FColor::Green,
			FString::Printf(TEXT("Coping Name From Game instance %s"),*CustomGameInstance->GetPlayerName()));
	}
}

void AJtcPlayerStates::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

FString AJtcPlayerStates::GetPlayerNameCustom() const
{
	return PlayerName;
}

void AJtcPlayerStates::SetCustomPlayerName(FString CustomPlayerName)
{
	PlayerName = CustomPlayerName;
}
