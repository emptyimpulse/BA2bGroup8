// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PointDisplayActor.h"

#include "Subsystems/JTCGameState.h"

// Sets default values
APointDisplayActor::APointDisplayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TraitorPoints = CreateDefaultSubobject<UTextRenderComponent>("PointDisplayActor");
	SolverPoints = CreateDefaultSubobject<UTextRenderComponent>("SolverPointDisplayActor");
	RootComponent = TraitorPoints;
	SolverPoints->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APointDisplayActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointDisplayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointDisplayActor::UpdateScoreOnDisplay()
{
	AJTCGameState* CustomGameState = GetWorld()->GetGameStateChecked<AJTCGameState>();
	if (CustomGameState)
	{
		TraitorPoints->SetText(FText::Format(FText::FromString("Traitor Score : {0}"),CustomGameState->FailedPuzzles));
		SolverPoints->SetText(FText::Format(FText::FromString("Solvers Score : {0}"), CustomGameState->SolvedPuzzles));
	}
}

