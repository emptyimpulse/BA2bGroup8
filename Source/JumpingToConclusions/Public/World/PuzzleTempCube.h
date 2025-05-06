// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActors.h"
#include "GameFramework/Actor.h"
#include "Widget/PuzzleAnswerDisplay.h"
#include "PuzzleTempCube.generated.h"

class USphereComponent;

UCLASS()
class JUMPINGTOCONCLUSIONS_API APuzzleTempCube : public AInteractableActors
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTempCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//--------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------PROPERTIES--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedPuzzle)
	bool bIsPuzzleSolved = false;

	FTimerHandle SwapColourTimer;
	//--------------------------------------------------------------------------------------------------------------//
	//---------------------------------------------------FUNCTIONS--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//
	UFUNCTION()
	void OnRep_ReplicatedPuzzle();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
						 AActor* OtherActor,
						 UPrimitiveComponent* OtherComp,
						 int32 OtherBodyIndex,
						 bool bFromSweep,
						 const FHitResult& SweepResult);
public:
	//--------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------PROPERTIES--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PuzzleCube;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* BlueShiftMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial* RedShiftMaterial;

	UPROPERTY()
	USphereComponent* SphereComponent;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPuzzleAnswerDisplay> WidgetReference;

	UPROPERTY()
	UPuzzleAnswerDisplay* CreatedWidget;
	

	UPROPERTY(Replicated)
	int32 PuzzleIndex;

	
	//--------------------------------------------------------------------------------------------------------------//
	//---------------------------------------------------FUNCTIONS--------------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------//
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Server,Reliable)
	void SetIsPuzzleSolved();
	
	FORCEINLINE int32 GetPuzzleIndex() { return PuzzleIndex; }
	FORCEINLINE bool IsPuzzleSolved() const { return bIsPuzzleSolved; }

	UFUNCTION(Client,Reliable)
	void ShowOnPlayerScreen(APlayerController* Player);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Interact(AJumpingToConclusionsCharacter* InstigatingPlayer) override;
};
