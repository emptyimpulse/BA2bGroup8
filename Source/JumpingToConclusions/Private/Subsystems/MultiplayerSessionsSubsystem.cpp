// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	//PrintString(("MSS Constructor"));

	CreateServerAfterDestroy = false;
	DestroyServerName = "";
	ServerNameToFind = "";
	MySessionName = FName("JumpingToConclusion Session");

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

			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(
				this,
				&UMultiplayerSessionsSubsystem::OnDestroySessionComplete);

			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
				this,
				&UMultiplayerSessionsSubsystem::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(
				this,
				&UMultiplayerSessionsSubsystem::OnJoinSessionComplete);
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
	
	FNamedOnlineSession * ExistingSession = SessionInterface->GetNamedSession(MySessionName);
	if(ExistingSession)
	{
		FString Msg = FString::Printf(TEXT("Session with name %s already exists, Destroying it"), *MySessionName.ToString());
		PrintString(Msg);
		CreateServerAfterDestroy = true;
		DestroyServerName = ServerName;
		SessionInterface->DestroySession(MySessionName);
		return;
	}
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
	if (IsLan)
	{
		PrintString("Server isLan");
	}
	else
	{
		PrintString("Server is not lan");
	}
	SessionSettings.bIsLANMatch = IsLan;
	SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
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
		PrintString(FString::Printf(TEXT("OnCreateSessionComplete: %s"), *SessionName.ToString()));
		GetWorld()->ServerTravel("/Game/Lobby/LobbyLevel?Listen");
	}
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	FString Msg = FString::Printf(TEXT("OnDestroySessionComplete: SessionName %s,Success: %d"),
		*SessionName.ToString(),
		bWasSuccessful);
	PrintString(Msg);

	if (CreateServerAfterDestroy)
	{
		CreateServerAfterDestroy = false;
		CreateServer(DestroyServerName);
	}
	
	
}


void UMultiplayerSessionsSubsystem::FindServer(FString ServerName)
{
	PrintString("Find Server");

	if (ServerName.IsEmpty())
	{
		PrintString("Server Name Cannot be empty!");
		return;
	}

	SessionSearch= MakeShareable(new FOnlineSessionSearch());
	bool IsLan = false;
	if(IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLan = true;

	}
	if (IsLan)
	{
		PrintString("Server isLan");
	}
	else
	{
		PrintString("Server is not lan");
	}
	SessionSearch->bIsLanQuery = IsLan;
	SessionSearch->MaxSearchResults = 9999;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	ServerNameToFind = ServerName;
	
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UMultiplayerSessionsSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{

	if(!bWasSuccessful) return;
	if(ServerNameToFind.IsEmpty()) return;
	
	TArray<FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;
	FOnlineSessionSearchResult* CorrectResult = 0;

	
	if (Results.Num() > 0)
	{
		FString Msg = FString::Printf(TEXT("Found Sessions: %d"), Results.Num());
		PrintString(Msg);

		for(FOnlineSessionSearchResult Result : Results)
		{
			if (Result.IsValid())
			{
				FString ServerName = "No-Name";
				Result.Session.SessionSettings.Get(FName("SERVER_NAME"),ServerName);
				

				if(ServerName.Equals(ServerNameToFind))
				{
					CorrectResult = &Result;
					FString MSg = FString::Printf(TEXT("Found Server with name = %s"), *ServerName);
					PrintString(MSg);
					break;
				}
			}
		}
		
		if (CorrectResult)
		{

			SessionInterface->JoinSession(0,MySessionName, *CorrectResult);
		}
		else
		{
			PrintString(FString::Printf(TEXT("Couldnt Find Server with name = %s"), *ServerNameToFind));
			ServerNameToFind = "";
		}
	}
	else
	{
		PrintString("Zero Session Found");
	}
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(Result==EOnJoinSessionCompleteResult::Success)
	{
		FString MSg = FString::Printf(TEXT("Successfully joined session %s"), *SessionName.ToString());
		PrintString(MSg);

		FString Address = "";
		bool Success = SessionInterface->GetResolvedConnectString(MySessionName, Address);
		if (Success)
		{
			PrintString(FString::Printf(TEXT("Connected to %s"), *Address));
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PrintString("ClientTravel initilizing");
				PlayerController->ClientTravel(Address, TRAVEL_Absolute);
			}
		}
		else
		{
			PrintString("GetReslovedConnectString failed");
		}
	}
	else
	{
		PrintString("OnJoinSessionComplete: Failed");
	}
}



void UMultiplayerSessionsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	//UE_LOG(LogTemp,Warning,TEXT("MSS Reinitialize"));
}
