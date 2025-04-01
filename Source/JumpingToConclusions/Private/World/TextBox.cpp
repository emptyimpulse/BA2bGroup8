// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TextBox.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATextBox::ATextBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.0f;
}

// Called when the game starts or when spawned
void ATextBox::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TestTimer,
			this,
			&ATextBox::MulticastRPCExplode
			,2.0f, false);
	}
}

// Called every frame
void ATextBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Server");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Green,"Client");
	}*/
}


void ATextBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATextBox,ReplicatedVar)
}

void ATextBox::OnRep_ReplicatedVar()
{
	if(HasAuthority())
	{
		FVector NewLocation = GetActorLocation() + FVector(0.0f,0.0f,200.0f);
		SetActorLocation(NewLocation);
		
		//GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Server: OnRep_ReplicatedVar");
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Green,FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
	}
}
void ATextBox::DecreaseReplicatedVar()
{
	if (HasAuthority())
	{
		ReplicatedVar -= 1.0f;
		OnRep_ReplicatedVar();
		if (ReplicatedVar > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(
			TestTimer,
			this,
			&ATextBox::DecreaseReplicatedVar
			,2.0f, false);
		}
	}
}

void ATextBox::MulticastRPCExplode_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,
	"Server: MulticastRPCElxplode_Implementation");
		GetWorld()->GetTimerManager().SetTimer(
		TestTimer,
		this,
		&ATextBox::MulticastRPCExplode
		,2.0f,
		false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Green,
	"Client: ServerRPCFunction_Implementation");
	}

	if (!IsRunningDedicatedServer())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation(),
			FRotator::ZeroRotator,
			true,
			EPSCPoolMethod::AutoRelease);
	}
}


