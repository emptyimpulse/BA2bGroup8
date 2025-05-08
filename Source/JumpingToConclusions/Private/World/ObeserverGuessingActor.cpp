// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ObeserverGuessingActor.h"

#include "Components/TextRenderComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AObeserverGuessingActor::AObeserverGuessingActor()
{
	SceneAsset = CreateDefaultSubobject<UStaticMeshComponent>("SceneAsset");
	SetRootComponent(SceneAsset);
	
	PlayerNameDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextBlock"));
	PlayerNameDisplay->SetupAttachment(SceneAsset);
	
	InteractDistance = CreateDefaultSubobject<USphereComponent>(TEXT("InteractDistance"));
	InteractDistance->SetupAttachment(SceneAsset);
	InteractDistance->SetCollisionProfileName(TEXT("ObeserverGuessingActor"));
	InteractDistance->InitSphereRadius(150.0f);
	InteractDistance->SetGenerateOverlapEvents(true);
	
}

void AObeserverGuessingActor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
	AJTCGameState* CustomGameState = Cast<AJTCGameState>(UGameplayStatics::GetGameState(this));
	if (CustomGameState)
	{
		CustomGameState->OnObserverDelegate.AddUObject(this,&AObeserverGuessingActor::SetPlayerChosenIndex);
	}
}

void AObeserverGuessingActor::SetPlayerChosenIndex()
{
	AJTCGameState* CustomGameState = GetWorld()->GetGameStateChecked<AJTCGameState>();
	PlayerNameDisplay->SetText(FText::FromString(
		"Player: "+ ChosenPlayerController->GetName()));
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Purple,ChosenPlayerController->GetName());
}

void AObeserverGuessingActor::Interact_Implementation(AJumpingToConclusionsCharacter* InstigatingPlayer)
{
	if (ChosenPlayerController != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Purple,ChosenPlayerController->GetName());
		AJumpingToConclusionsCharacter* PC = InstigatingPlayer;
		if (PC)
		{
			PC->ServerPickTraitor(ChosenPlayerController);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Purple,"ChosenPlayerIsNull");
	}
	
}

void AObeserverGuessingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AObeserverGuessingActor,ChosenPlayerController);
}

