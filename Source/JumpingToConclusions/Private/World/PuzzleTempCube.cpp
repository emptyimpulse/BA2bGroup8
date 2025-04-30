// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PuzzleTempCube.h"

#include "Components/SphereComponent.h"
#include "JumpingToConclusions/JumpingToConclusionsCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/JTCGameState.h"

// Sets default values
APuzzleTempCube::APuzzleTempCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PuzzleCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(PuzzleCube);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Component"));
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->InitSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName(TEXT("OverLapPlayer"));
	SphereComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void APuzzleTempCube::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&APuzzleTempCube::OnSphereOverlap);
}
// Called every frame
void APuzzleTempCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void APuzzleTempCube::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AJumpingToConclusionsCharacter* OnePlayerCharacter = Cast<AJumpingToConclusionsCharacter>(OtherActor))
	{
		SetIsPuzzleSolved();
	}
}

void APuzzleTempCube::OnRep_ReplicatedPuzzle()
{
	if (!PuzzleCube || !BlueShiftMaterial || !RedShiftMaterial) return;

	if (bIsPuzzleSolved)
	{
		PuzzleCube->SetMaterial(0, RedShiftMaterial);

	}
	else
	{
		PuzzleCube->SetMaterial(0, BlueShiftMaterial);

	}
}

void APuzzleTempCube::SetIsPuzzleSolved_Implementation()
{
	if (HasAuthority())
	{
		if (bIsPuzzleSolved == true)
		{
			bIsPuzzleSolved = false;
			if (AJTCGameState* CustomGameState = GetWorld()->GetGameStateChecked<AJTCGameState>())
			{
				GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,
					"PuzzleTempCube::GetGameState Good");
				CustomGameState->AddSolvedPuzzleScore(true);
			}
		}
		else
		{
			bIsPuzzleSolved = true;
		}
		OnRep_ReplicatedPuzzle();
	}
}
void APuzzleTempCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APuzzleTempCube,bIsPuzzleSolved);
}

