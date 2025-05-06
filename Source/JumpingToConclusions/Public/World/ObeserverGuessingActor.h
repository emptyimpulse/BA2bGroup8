// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/InteractableActors.h"
#include "ObeserverGuessingActor.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API AObeserverGuessingActor : public AInteractableActors
{
	GENERATED_BODY()

public:
	AObeserverGuessingActor();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneAsset;

	UPROPERTY(EditDefaultsOnly)
	UTextBlock* PlayerNameDisplay;

	UPROPERTY(Replicated)
	bool PlayerIndex;

	UPROPERTY()
	APlayerController* ChosenPlayerController;
	
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(AJumpingToConclusionsCharacter* InstigatingPlayer) override;
};
