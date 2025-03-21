// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TextBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATextBox::ATextBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.0f;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATextBox::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
}

// Called every frame
void ATextBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Server");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Green,"Client");
	}
}

void ATextBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATextBox,ReplicatedVar)
}

