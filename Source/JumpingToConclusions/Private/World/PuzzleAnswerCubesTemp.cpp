// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PuzzleAnswerCubesTemp.h"

#include "JtcPlayerController.h"
#include "Components/SphereComponent.h"
#include "JumpingToConclusions/JumpingToConclusionsCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/PuzzleAnswerSheet.h"

// Sets default values
APuzzleAnswerCubesTemp::APuzzleAnswerCubesTemp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>("OverLap Sphere");
	OverlapSphere->InitSphereRadius(100.0f);
	OverlapSphere->SetupAttachment(StaticMesh);
	OverlapSphere->SetCollisionProfileName(TEXT("OverLapPlayer"));
	OverlapSphere->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void APuzzleAnswerCubesTemp::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this,&APuzzleAnswerCubesTemp::OnSphereOverlap);
}

// Called every frame
void APuzzleAnswerCubesTemp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APuzzleAnswerCubesTemp::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APuzzleAnswerCubesTemp::Interact_Implementation(AJumpingToConclusionsCharacter* InstigatingPlayer)
{
	if (AJumpingToConclusionsCharacter* PC = Cast<AJumpingToConclusionsCharacter>(InstigatingPlayer))
	{
		if (AJtcPlayerController* PlayerCont = Cast<AJtcPlayerController>(PC->GetController()))
		{
			if (IsValid(WidgetReference))
			{
				GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,"Showing OnScreen");

				ShowOnPlayerScreen(PlayerCont);
			}
		}
	}
}


void APuzzleAnswerCubesTemp::ShowOnPlayerScreen_Implementation(APlayerController* Player)
{
	
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Widget Passed");
	CreatedWidget = CreateWidget<UPuzzleAnswerSheet>(Player, WidgetReference);
	if (CreatedWidget)
	{
		CreatedWidget->AnswerIndex = AnswerCubeIndex;
		CreatedWidget->AddToPlayerScreen();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Widget not created"));
	}
	
	const FInputModeUIOnly InputMode;
	Player->SetInputMode(InputMode);
	Player->SetShowMouseCursor(true);
}

