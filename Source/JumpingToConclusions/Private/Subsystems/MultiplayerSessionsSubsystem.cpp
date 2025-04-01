// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "SWarningOrErrorBox.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	//PrintString(("MSS Constructor"));
}

void UMultiplayerSessionsSubsystem::PrintString(const FString& Str)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,Str);
	}
}


void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//PrintSring(("MSS Initialize"));

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		FString Subsystemname = OnlineSubsystem->GetSubsystemName().ToString();
		PrintString(Subsystemname);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this,
				&UMultiplayerSessionsSubsystem::OnCreateSessionComplete);
		}
		
	}

}

void UMultiplayerSessionsSubsystem::CreateServer(FString ServerName)
{
	PrintString("Create Server");

	if(ServerName.IsEmpty())
	{
		PrintString("Server Name Cannot be empty!");
		return;
	}

	FName MySessionName = FName("JumpingToConclusion Session");

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = true;
	SessionSettings.bShouldAdvertise = true;
	//maximum amount of players
	SessionSettings.NumPublicConnections = 8;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowJoinViaPresence = true;
	bool IsLan = false;
	if(IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLan = true;
	}
	SessionSettings.bIsLANMatch = IsLan;
	
	SessionInterface->CreateSession(0,MySessionName,SessionSettings);
	if(SessionInterface.IsValid())
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
			this,
			&UMultiplayerSessionsSubsystem::OnCreateSessionComplete);
	}
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	PrintString(FString::Printf(TEXT("OnCreateSessionComplete: %d"), bWasSuccessful));

	if (bWasSuccessful)
	{
		GetWorld()->ServerTravel("/Game/JumpingToConclusions/Maps/GameLevel?Listen");
	}
}

void UMultiplayerSessionsSubsystem::FindServer(FString ServerName)
{
	PrintString("Find Server");
}


void UMultiplayerSessionsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	//UE_LOG(LogTemp,Warning,TEXT("MSS Reinitialize"));
}
