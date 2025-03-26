// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MultiplayerSessionsSubsystem.h"

#include "SWarningOrErrorBox.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	PrintSring(("MSS Constructor"));
}

void UMultiplayerSessionsSubsystem::PrintSring(const FString& Str)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,Str);
	}
}
void UMultiplayerSessionsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp,Warning,TEXT("MSS Deinitilize"));
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	PrintSring(("MSS Initilize"));

}

